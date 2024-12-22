#include "GameResult.h"
#include "Camera.h"

using namespace DirectX::SimpleMath;

GameUI::GameUI()
{

}

GameUI::~GameUI()
{

}

void GameUI::Init(std::string TexPaht)
{
	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

	// �}�e���A������
	MATERIAL	rmtrl;
	rmtrl.Ambient = Color(0, 0, 0, 0);
	rmtrl.Diffuse = Color(1, 1, 1, 1);
	rmtrl.Emission = Color(0, 0, 0, 0);
	rmtrl.Specular = Color(0, 0, 0, 0);
	rmtrl.Shiness = 0;
	rmtrl.TextureEnable = TRUE;

	m_Material.Create(rmtrl);



	m_Texture.Load(TexPaht);

}

void GameUI::Update(DirectX::SimpleMath::Matrix viewM, DirectX::SimpleMath::Matrix ProjM)
{
	// �J��������r���[�s��ƃv���W�F�N�V�����s����擾
	DirectX::SimpleMath::Matrix viewMatrix = viewM;  // �J�����N���X��GetViewMatrix()���g�p
	DirectX::SimpleMath::Matrix projectionMatrix = ProjM;  // �J�����N���X��GetProjectionMatrix()���g�p

	// 3D�̃��[���h��ԍ��W (��FUI�̒����ʒu)
	DirectX::SimpleMath::Vector3 worldPosition(Center.x, Center.y, 0.0f);

	// ���[���h�A�r���[�A�v���W�F�N�V�����s����g���ăX�N���[�����W�ɕϊ�
	DirectX::SimpleMath::Vector4 screenPosition = DirectX::XMVector4Transform(DirectX::SimpleMath::Vector4(worldPosition.x, worldPosition.y, worldPosition.z, 1.0f), viewMatrix * projectionMatrix);

	// NDC (���K���f�o�C�X���W)����X�N���[�����W�֕ϊ�
	screenPosition.x /= screenPosition.w;
	screenPosition.y /= screenPosition.w;

	// �X�N���[�����W�ɕϊ����ꂽ���ʂ�UI�̒����ʒu�ɐݒ�
	Center.x = (screenPosition.x + 1.0f) * 0.5f * 1920;
	Center.y = (1.0f - screenPosition.y) * 0.5f * 1080; // Y�������]���Ă���ꍇ
}

void GameUI::Draw()
{

	Renderer::SetWorldViewProjection2D();
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();

	m_Shader.SetGPU();
	m_Material.SetGPU();

	//�����`�̂S���_�̈ʒu
	std::vector<VERTEX_3D> rectVertices(4);

	rectVertices[0].Position = Vector3(Center.x - halfWidth / 2, Center.y - halfHeight / 2, 0);
	rectVertices[1].Position = Vector3(Center.x + halfWidth / 2, Center.y - halfHeight / 2, 0);
	rectVertices[2].Position = Vector3(Center.x - halfWidth / 2, Center.y + halfHeight / 2, 0);
	rectVertices[3].Position = Vector3(Center.x + halfWidth / 2, Center.y + halfHeight / 2, 0);

	rectVertices[0].TexCoord = Vector2(0, 0);
	rectVertices[1].TexCoord = Vector2(1, 0);
	rectVertices[2].TexCoord = Vector2(0, 1);
	rectVertices[3].TexCoord = Vector2(1, 1);

	for (int i = 0; i < 4; ++i)
	{
		rectVertices[i].Diffuse = color;
	}

	//�V�F�[�_�[�ɃZ�b�g
	m_VertexBuffer.Create(rectVertices);
	m_VertexBuffer.SetGPU();
	m_Texture.SetGPU();

	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);
}

void GameUI::SetFadePos(DirectX::SimpleMath::Vector3 Fadepos)
{
	this->Center.x = Fadepos.x;
	this->Center.y = Fadepos.z;
}

DirectX::SimpleMath::Vector3 GameUI::GetFadePos()
{
	DirectX::SimpleMath::Vector3 Fadepos;
	Fadepos.x = this->Center.x;
	Fadepos.z = this->Center.y;

	return Fadepos;

}

void GameUI::SetPosition(DirectX::SimpleMath::Vector3 position)
{
	// 3D��ԏ�̍��W��UI�̒����ʒu�Ƃ��Đݒ�
	Center.x = position.x;
	Center.y = position.y;
}
