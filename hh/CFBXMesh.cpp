#include "CFBXMesh.h"
#include <iostream>

void CFBXMesh::LoadFBX(std::string filename, std::string texturedirectory) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    ProcessNode(scene->mRootNode, scene);
}

void CFBXMesh::ProcessNode(aiNode* node, const aiScene* scene) {
    // ノード内の全てのメッシュを処理
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    // 子ノードを再帰的に処理
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

void CFBXMesh::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
    std::vector<VERTEX_3D> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        VERTEX_3D vertex;
        vertex.Position = DirectX::SimpleMath::Vector3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
        vertex.Normal = DirectX::SimpleMath::Vector3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
        if (mesh->mTextureCoords[0]) {
            vertex.TexCoord = DirectX::SimpleMath::Vector2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.TexCoord = DirectX::SimpleMath::Vector2(0.0f, 0.0f);
        }

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // 頂点とインデックスをメンバ変数に追加
    m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end());
    m_indices.insert(m_indices.end(), indices.begin(), indices.end());

    // マテリアル情報を処理
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        MATERIAL mat;
        aiColor4D color;
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, color)) {
            mat.Diffuse = DirectX::SimpleMath::Color(color.r, color.g, color.b, color.a);
        }
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, color)) {
            mat.Specular = DirectX::SimpleMath::Color(color.r, color.g, color.b, color.a);
        }
        if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, color)) {
            mat.Ambient = DirectX::SimpleMath::Color(color.r, color.g, color.b, color.a);
        }
        float shininess;
        if (AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess)) {
            mat.Shiness = shininess;
        }

        m_materials.push_back(mat);
    }
}
