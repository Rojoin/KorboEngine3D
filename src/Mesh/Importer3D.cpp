#include "Importer3D.h"

#include <iostream>

#include "Model.h"
#include "Sprite/Importer2D.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

string Importer3D::currentDirectory = "";
vector<Texture> Importer3D::texturesLoaded;

void Importer3D::loadModel(const string& path, string& directory, vector<BasicMesh>& meshes, bool shouldInvertUVs,
                           Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    currentDirectory = path.substr(0, path.find_last_of('/'));
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(model->meshes, scene->mRootNode, scene, shouldInvertUVs, model);
}


void Importer3D::processNode(vector<BasicMesh>& meshes, aiNode* node, const aiScene* scene, bool shouldInvertUVs,
                             Model* model)
{
    // process all the node's meshes (if any)

    Model* modelToUse = model;
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, shouldInvertUVs));
    }
    if (node->mNumMeshes > 0)
    {
        modelToUse = new Model(model->GetRenderer(), model->tranform);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(modelToUse->meshes, node->mChildren[i], scene, shouldInvertUVs, modelToUse);
    }
}

BasicMesh Importer3D::processMesh(aiMesh* mesh, const aiScene* scene, bool shouldInvertUVs)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;

        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        if (mesh->mTextureCoords[0])
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            // tangent
            vector.x = mesh->mTangents[i].x;
            vector.y = mesh->mTangents[i].y;
            vector.z = mesh->mTangents[i].z;
            vertex.Tangent = vector;
            // bitangent
            vector.x = mesh->mBitangents[i].x;
            vector.y = mesh->mBitangents[i].y;
            vector.z = mesh->mBitangents[i].z;
            vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        vertices.push_back(vertex);
    }
    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process material

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse",
                                                           shouldInvertUVs);
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular",
                                                            shouldInvertUVs);
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        vector<Texture> baseColorMaps = loadMaterialTextures(material, aiTextureType_BASE_COLOR, "texture_baseColor",
                                                             shouldInvertUVs);
        textures.insert(textures.end(), baseColorMaps.begin(), baseColorMaps.end());

        vector<Texture> normalsMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "texture_normals",
                                                           shouldInvertUVs);
        textures.insert(textures.end(), normalsMaps.begin(), normalsMaps.end());

        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_height",
                                                               shouldInvertUVs);
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        std::vector<Texture> metallicMaps = loadMaterialTextures(material, aiTextureType_METALNESS, "texture_metalness",
                                                                 shouldInvertUVs);
        textures.insert(textures.end(), metallicMaps.begin(), metallicMaps.end());

        std::vector<Texture> roughnessMaps = loadMaterialTextures(material, aiTextureType_SHININESS,
                                                                  "texture_roughness", shouldInvertUVs);
        textures.insert(textures.end(), roughnessMaps.begin(), roughnessMaps.end());
    }
    if (scene->HasMaterials())
    {
    }
    return BasicMesh(vertices, indices, textures);
}

vector<Texture> Importer3D::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName,
                                                 bool shouldInvertUVs)
{
    vector<Texture> textures;
    unsigned int textureCount = mat->GetTextureCount(type);
    for (unsigned int i = 0; i < textureCount; i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < texturesLoaded.size(); j++)
        {
            if (std::strcmp(texturesLoaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(texturesLoaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip)
        {
            // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = Importer2D::TextureFromFile(str.C_Str(), currentDirectory, shouldInvertUVs);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            texturesLoaded.push_back(texture); // add to loaded textures
        }
    }
    return textures;
}
