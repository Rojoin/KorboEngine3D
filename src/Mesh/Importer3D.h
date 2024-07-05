﻿#pragma once
#include <assimp/scene.h>

#include <string>
#include <sstream>

#include "Model.h"
class Transform;

static class Importer3D
{
private:
    static string currentDirectory;
    static vector<Texture> texturesLoaded; 
public:
    static void loadModel(const string& path, string& directory, vector<BasicMesh>& meshes,bool shouldInvertUVs, Transform* transform);
    static void processNode(vector<BasicMesh>& meshes, aiNode* node, const aiScene* scene, bool shouldInvertUVs, Transform* transform);
    static BasicMesh processMesh(aiMesh *mesh, const aiScene *scene,bool shouldInvertUVs);
    static vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, 
                                     string typeName,bool shouldInvertUVs);
};
