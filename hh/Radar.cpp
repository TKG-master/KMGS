#include "Radar.h"
#include "Enemy.h"
#include <d3d11.h>

using namespace DirectX::SimpleMath;


void Radar::Init()
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

	m_Texture.Load("assets\\siro.jpg");

}

void Radar::Update(DirectX::SimpleMath::Vector3 playerPosition, const std::vector<DirectX::SimpleMath::Vector3>& enemyPositions)
{

	playerpos = playerPosition;

	// �v���C���[�̈ʒu�����[�_�[�̒��S�ɐݒ�
	m_RadarCenter = Vector2(playerPosition.x, playerPosition.z);

	// �G�̈ʒu���X�g���N���A���čX�V
	m_EnemyPositions.clear();

	// ���[�_�[�̒����`�̃T�C�Y
	float radarWidth = 250.0f;
	float radarHeight = 150.0f;

	// �X�P�[�����O�t�@�N�^�[�i���G�͈͂��L���邽�߂̌W���j
	float scaleFactor = 3.0f;

	// �X�P�[�����O��̒����`�̃T�C�Y
	float scaledWidth = radarWidth * scaleFactor;
	float scaledHeight = radarHeight * scaleFactor;

	// �e�G�̈ʒu������
	for (const auto& enemyPosition : enemyPositions)
	{
		// �v���C���[����G�܂ł̑��Έʒu���v�Z
		Vector2 relativePos(enemyPosition.x - playerPosition.x, enemyPosition.z - playerPosition.z);

		// �X�P�[�����O��͈͓̔��ɓG�����邩�ǂ������m�F
		if (abs(relativePos.x) <= scaledWidth / 2 && abs(relativePos.y) <= scaledHeight / 2)
		{
			// �͈͓��ɂ���ꍇ�A���[�_�[�̈ʒu�ɕϊ����ĕۑ�
			Vector2 radarPos;
			radarPos.x = relativePos.x * (radarWidth / scaledWidth);
			radarPos.y = -relativePos.y * (radarHeight / scaledHeight); // Y���W�̕����𔽓]
			m_EnemyPositions.push_back(radarPos); // �G�̈ʒu�����X�g�ɒǉ�
		}
	}

}

void Radar::Draw(const std::vector<Enemy*>& enemies)
{

	Renderer::SetWorldViewProjection2D();
	ID3D11DeviceContext* devicecontext = Renderer::GetDeviceContext();

	m_Shader.SetGPU();
	m_Material.SetGPU();

	// ���[�_�[�̒��S��ݒ�
	Vector2 radarCenter = Vector2(1100, 100); // ���[�_�[�̉�ʏ�̈ʒu
	//�����Əc��
	float width = 250.0f;
	float height = 150.0f;


	//�����`�̂S���_�̈ʒu
	std::vector<VERTEX_3D> rectVertices(4);

	rectVertices[0].Position = Vector3(radarCenter.x - width / 2, radarCenter.y - height / 2, 0);
	rectVertices[1].Position = Vector3(radarCenter.x + width / 2, radarCenter.y - height / 2, 0);
	rectVertices[2].Position = Vector3(radarCenter.x - width / 2, radarCenter.y + height / 2, 0);
	rectVertices[3].Position = Vector3(radarCenter.x + width / 2, radarCenter.y + height / 2, 0);

	//�����`�̐F
	Color radarColor(0, 0.5, 0.5, 0.5f);
	for (int i = 0; i < 4; ++i)
	{
		rectVertices[i].Diffuse = radarColor;
	}

	//�V�F�[�_�[�ɃZ�b�g
	m_VertexBuffer.Create(rectVertices);
	m_VertexBuffer.SetGPU();
	m_Texture.SetGPU();
	
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);

	// �e�G�̈ʒu��`��
	for (size_t i = 0; i < m_EnemyPositions.size(); ++i)
	{
		Vector2 enemyPos = radarCenter + m_EnemyPositions[i];
		std::vector<VERTEX_3D> enemyVertices(4);

		float enemySize = 2.0f; // �G�̎l�p�`�̃T�C�Y
		enemyVertices[0].Position = Vector3(enemyPos.x - enemySize, enemyPos.y - enemySize, 0);
		enemyVertices[1].Position = Vector3(enemyPos.x + enemySize, enemyPos.y - enemySize, 0);
		enemyVertices[2].Position = Vector3(enemyPos.x - enemySize, enemyPos.y + enemySize, 0);
		enemyVertices[3].Position = Vector3(enemyPos.x + enemySize, enemyPos.y + enemySize, 0);

		Color enemyColor(1, 0, 0, 1);
		for (int i = 0; i < 4; ++i)
		{
			enemyVertices[i].Diffuse = enemyColor;
		}

		m_VertexBuffer.Create(enemyVertices);
		m_VertexBuffer.SetGPU();

		devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		devicecontext->Draw(4, 0);

		Enemy* enemy = enemies[i];
		float fanRadius = enemy->Getlength()/3.14f; // ��^�̔��a�i���싗�����k�����ĕ\���j
		float viewAngle = enemy->GetFov(); // ����p
		Vector2 radarEnemyPosition = radarCenter + m_EnemyPositions[i]; // ���[�_�[��̓G�̈ʒu
		Vector2 forward = Vector2(enemy->Getforward().x,enemy->Getforward().z); // �G�̌����Ă������

		forward.y = forward.y * -1;

		int numSegments = 20; // ��^�̃Z�O�����g��

		std::vector<VERTEX_3D> fanVertices(numSegments + 2); // ��^�̒��_��

		// ���S�_�̐ݒ�
		fanVertices[0].Position = Vector3(radarEnemyPosition.x, radarEnemyPosition.y, 0);
		Color fanColor(0, 0.8, 0.8, 0.8f);
		fanVertices[0].Diffuse = fanColor;

		// ��^�̃Z�O�����g���v�Z
		for (int i = 0; i <= numSegments; ++i)
		{
			float angle = -viewAngle / 2 + viewAngle * i / numSegments;

			// forward�x�N�g���̕����ɉ����Ċp�x���v�Z
			float radian = atan2(forward.y, forward.x);
			float x = radarEnemyPosition.x + cos(radian + angle) * fanRadius;
			float y = radarEnemyPosition.y + sin(radian + angle) * fanRadius;
			fanVertices[i + 1].Position = Vector3(x, y, 0);
			fanVertices[i + 1].Diffuse = fanColor;

		}

		// ��^�̒��_���O�p�`���X�g�ŕ`�悷�邽�߂̃o�b�t�@��ݒ�
		std::vector<VERTEX_3D> fanIndices;
		for (int i = 1; i < numSegments + 1; ++i)
		{
			fanIndices.push_back(fanVertices[0]);
			fanIndices.push_back(fanVertices[i]);
			fanIndices.push_back(fanVertices[i + 1]);
		}

		m_VertexBuffer.Create(fanIndices);
		m_VertexBuffer.SetGPU();

		// ��^�̕`��p�g�|���W�[���O�p�`���X�g�ɐݒ�
		devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		devicecontext->Draw(fanIndices.size(), 0);
		}

	// ���[�_�[�̒��S�ɔ����_��`��
	float pointSize = 2.0f; // �_�̃T�C�Y

	std::vector<VERTEX_3D> pointVertices(4); // 4 vertices for a small square representing the point

	// �_�̒��_��ݒ�
	pointVertices[0].Position = Vector3(radarCenter.x - pointSize / 2, radarCenter.y - pointSize / 2, 0);
	pointVertices[1].Position = Vector3(radarCenter.x + pointSize / 2, radarCenter.y - pointSize / 2, 0);
	pointVertices[2].Position = Vector3(radarCenter.x - pointSize / 2, radarCenter.y + pointSize / 2, 0);
	pointVertices[3].Position = Vector3(radarCenter.x + pointSize / 2, radarCenter.y + pointSize / 2, 0);

	Color pointColor(1, 1, 1, 1); // ���F
	for (int i = 0; i < 4; ++i)
	{
		pointVertices[i].Diffuse = pointColor;
	}

	// �_�p�̒��_�o�b�t�@��ݒ�
	m_VertexBuffer.Create(pointVertices);
	m_VertexBuffer.SetGPU();

	// �g�|���W�[���O�p�`�X�g���b�v�ɐݒ�
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	devicecontext->Draw(4, 0);
}


void Radar::Dispose()
{

}
