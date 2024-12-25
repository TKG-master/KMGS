#include "CFBXMeshRenderer.h"

void CFBXMeshRenderer::LoadFBX(const std::string& filename, const std::string& texturedirectory) {
    // FBXメッシュを読み込み
    CFBXMesh mesh;
    mesh.LoadFBX(filename, texturedirectory);

    // 基本的な初期化
    CStaticMeshRenderer::Init(mesh);
}

void CFBXMeshRenderer::Draw() {
    // 描画を行う
    CStaticMeshRenderer::Draw();
}
