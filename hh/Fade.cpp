#include "Fade.h"

using namespace DirectX::SimpleMath;

void Fade::Init()
{
    // ���_�f�[�^�̏����i�l�p�`�j
    std::vector<VERTEX_3D> vertices(4);

    // ���_�̈ʒu
    vertices[0].Position = Vector3(5000.0f, 0.0f, 0.0f);  // ����
    vertices[1].Position = Vector3(5000.0f, 0.0f, 0.0f);  // �E��
    vertices[2].Position = Vector3(5000.0f, 6000.0f, 0.0f);  // ����
    vertices[3].Position = Vector3(5000.0f, 6000.0f, 0.0f);  // �E��

    // ���_�̐F�i�����͊��S�ɓ����j
    for (int i = 0; i < 4; i++) {
        vertices[i].Diffuse = Color(1, 1, 1, 0);  // ����
    }

    // ���_�̃e�N�X�`�����W
    vertices[0].TexCoord = Vector2(0, 0);
    vertices[1].TexCoord = Vector2(1, 0);
    vertices[2].TexCoord = Vector2(0, 1);
    vertices[3].TexCoord = Vector2(1, 1);

    // ���_�o�b�t�@�̐���
    m_VertexBuffer.Create(vertices);

    // �C���f�b�N�X�f�[�^
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };
    m_IndexBuffer.Create(indices);

    // �V�F�[�_�[�̓ǂݍ���
    m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

    // �}�e���A���̐ݒ�i�����x���Ǘ��j
    MATERIAL mtrl;
    mtrl.Ambient = Color(0, 0, 0, 0);
    mtrl.Diffuse = Color(1, 1, 1, 0);
    mtrl.Emission = Color(0, 0, 0, 0);
    mtrl.Specular = Color(0, 0, 0, 0);
    mtrl.Shiness = 0;
    mtrl.TextureEnable = TRUE;
    m_Material.Create(mtrl);

    // �e�N�X�`���̓ǂݍ���
    bool sts = m_Texture.Load("assets\\kuro.png");
    assert(sts == true);

}

void Fade::Uninit()
{

}

void Fade::Draw()
{
	// 2D�`��p
	Renderer::SetWorldViewProjection2D();

	ID3D11DeviceContext* devicecontext;

	devicecontext = Renderer::GetDeviceContext();

	// �g�|���W�[���Z�b�g�i���v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_Shader.SetGPU();
	m_VertexBuffer.SetGPU();
	m_IndexBuffer.SetGPU();
	m_Material.SetGPU();
	m_Texture.SetGPU();

	devicecontext->DrawIndexed(
		4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

void Fade::FadeIn()
{
    m_FadingIn = true;
    m_IsFading = true;
}

void Fade::FadeOut()
{
    m_FadingIn = false;
    m_IsFading = true;
}

void Fade::Update()
{
    if (m_IsFading) {
        // �t�F�[�h�C�����t�F�[�h�A�E�g���̔���
        if (m_FadingIn) {
            m_Opacity += 0.05f;  // �����𒲐��i0.05�̓t�F�[�h�C���̃X�s�[�h�j
            if (m_Opacity >= 1.0f) {
                m_Opacity = 1.0f;
                m_IsFading = false;  // �t�F�[�h�C������
            }
        }
        else {
            m_Opacity -= 0.05f;  // �t�F�[�h�A�E�g�̑���
            if (m_Opacity <= 0.0f) {
                m_Opacity = 0.0f;
                m_IsFading = false;  // �t�F�[�h�A�E�g����
            }
        }

        // �s�����x���}�e���A���ɔ��f
        m_Material.SetDiffuse(Color(1.0f, 1.0f, 1.0f, m_Opacity));
        m_Material.SetGPU();
    }
}
