#pragma once
#include <assimp/scene.h>

#include <string>
#include <fstream>
#include <sstream>
#include "Model.h"

static class Importer3D
{
private:
    static string currentDirectory;
    static vector<Texture> texturesLoaded; 
public:
    static void loadModel(const string& path, string& directory, vector<BasicMesh>& meshes);
    static void processNode(vector<BasicMesh>& meshes,aiNode* node, const aiScene* scene);
    static BasicMesh processMesh(aiMesh *mesh, const aiScene *scene);
    static vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                     string typeName);
};
