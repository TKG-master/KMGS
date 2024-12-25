#pragma once
#include "CStaticMesh.h"
#include "AssimpPerse.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class CFBXMesh : public CStaticMesh {
public:
    void LoadFBX(std::string filename, std::string texturedirectory = "");

private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

