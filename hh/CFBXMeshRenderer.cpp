#include "CFBXMeshRenderer.h"

void CFBXMeshRenderer::LoadFBX(const std::string& filename, const std::string& texturedirectory) {
    // FBX���b�V����ǂݍ���
    CFBXMesh mesh;
    mesh.LoadFBX(filename, texturedirectory);

    // ��{�I�ȏ�����
    CStaticMeshRenderer::Init(mesh);
}

void CFBXMeshRenderer::Draw() {
    // �`����s��
    CStaticMeshRenderer::Draw();
}
