#include "Importer3D.h"

#include <iostream>
#include <glm/gtc/type_ptr.hpp>

#include "Model.h"
#include "Sprite/Importer2D.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "Base Game/Engine.h"

string Importer3D::currentDirectory = "";
vector<Texture> Importer3D::texturesLoaded;

void Importer3D::loadModel(const string& path, string& directory, vector<BasicMesh>& meshes, bool shouldInvertUVs,
                           Model* model, bool shouldBeTurnOffByBSP)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(
        path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace |
        aiProcess_JoinIdenticalVertices);
    currentDirectory = path.substr(0, path.find_last_of('/'));
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    processNode(model->meshes, scene->mRootNode, scene, shouldInvertUVs, model, shouldBeTurnOffByBSP);
}


void Importer3D::processNode(vector<BasicMesh>& meshes, aiNode* node, const aiScene* scene, bool shouldInvertUVs,
                             Model* model, bool shouldBeTurnOffByBSP)
{
    // process all the node's meshes (if any)
    aiMatrix4x4 aiTransform = node->mTransformation;
    aiVector3f aiPos;
    aiVector3f aiQua;
    aiVector3f aiSca;
    aiTransform.Decompose(aiSca, aiQua, aiPos);


    float RadianToDegree = (180 / Assimp::Math::aiPi<float>());
    Vec3 eulerAng = {aiQua.x * RadianToDegree, aiQua.y * RadianToDegree, aiQua.z * RadianToDegree};

    glm::mat4 nodeTransform = glm::transpose(glm::make_mat4(&aiTransform.a1));
    glm::vec3 posAux = nodeTransform[3];
    Vec3 pos = {posAux.x, posAux.y, posAux.z};
    Vec3 rot = {aiQua.x * RadianToDegree, aiQua.y * RadianToDegree, aiQua.z * RadianToDegree};
    Vec3 sca = {aiSca.x, aiSca.y, aiSca.z};
    Model* modelToUse = model;


    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        modelToUse = new Model(model->GetRenderer(), model->tranform, pos, rot, sca, shouldBeTurnOffByBSP);
        modelToUse->tranform->name = node->mName.C_Str();

        //Todo: Make bsp to be obtainable for name
        if (modelToUse->tranform->name.find("bspPlane") != string::npos)
        {
            Vec3 rotation;
            rotation = modelToUse->tranform->getRotation();
            cout << "Rotation: " << rotation.x << " " << rotation.y << " " << rotation.z << '\n';

            glm::vec3 point = modelToUse->tranform->getGlobalPositionGLM();
            glm::vec3 normal = modelToUse->tranform->getUp();

            model->GetRenderer()->engine->addPlaneToBSP(point, normal);
        }

        modelToUse->meshes.push_back(processMesh(mesh, scene, shouldInvertUVs));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(modelToUse->meshes, node->mChildren[i], scene, shouldInvertUVs, modelToUse, shouldBeTurnOffByBSP);
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
