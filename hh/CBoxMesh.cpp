#include	"CBoxMesh.h"

using namespace DirectX::SimpleMath;

struct FACE {
	unsigned int idx[3];
};

// �@���x�N�g�����v�Z
// ���_���W���m�[�}���C�Y
void BoxMesh::Normalize(
	Vector3 vec,
	Vector3& Normal) {

	vec.Normalize();
	Normal = vec;

}

void BoxMesh::DrawInit(float x, float y, float z,std::string TexPath)
{
	// �}�e���A������
	MATERIAL	mtrl;
	mtrl.Ambient = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Diffuse = DirectX::SimpleMath::Color(1, 1, 1, 1);
	mtrl.Emission = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Specular = DirectX::SimpleMath::Color(0, 0, 0, 0);
	mtrl.Shiness = 0;
	mtrl.TextureEnable = TRUE;

	this->Init(x, y, z, DirectX::SimpleMath::Color(1.0f, 1.0f, 1.0f, 1.0f),
		TexPath, "shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl", mtrl);

}

//�e�N�X�`�����g�p���Ȃ��ꍇNULL��\�L
void BoxMesh::Init(float width, float height, float depth, Color color,
	std::string TexPath = {}, std::string vShader, std::string pShader, MATERIAL mtrl)
{
	// �T�C�Y��ۑ�
	m_lengthx = width;
	m_lengthy = height;
	m_lengthz = depth;

	// �J���[�l��ۑ�
	m_color = color;

	// �C���f�b�N�X�f�[�^���쐬
	CreateIndex();

	// ���_�f�[�^���쐬
	CreateVertex();

	// �}�e���A������
	m_Material.Create(mtrl);

	// �V�F�[�_�I�u�W�F�N�g����
	m_Shader.Create(vShader, pShader);

	if (TexPath != "NULL")
	{
		m_Texture.Load(TexPath);
	}

	CMesh::Init();
}

void BoxMesh::Update()
{
	CMesh::Update();
}

void BoxMesh::Draw()
{
	CMesh::Draw();
}

// ���_�f�[�^����
void BoxMesh::CreateVertex() {

	// ���_�N���A
	m_vertices.clear();

	m_vertices.resize(12);
	m_vertices[0].Position.x = -(m_lengthx / 2.0f);
	m_vertices[0].Position.y = (m_lengthy / 2.0f);
	m_vertices[0].Position.z = -(m_lengthz / 2.0f);

	m_vertices[1].Position.x = (m_lengthx / 2.0f);
	m_vertices[1].Position.y = (m_lengthy / 2.0f);
	m_vertices[1].Position.z = -(m_lengthz / 2.0f);

	m_vertices[2].Position.x = (m_lengthx / 2.0f);
	m_vertices[2].Position.y = -(m_lengthy / 2.0f);
	m_vertices[2].Position.z = -(m_lengthz / 2.0f);

	m_vertices[3].Position.x = -(m_lengthx / 2.0f);
	m_vertices[3].Position.y = -(m_lengthy / 2.0f);
	m_vertices[3].Position.z = -(m_lengthz / 2.0f);


	m_vertices[4].Position.x = -(m_lengthx / 2.0f);
	m_vertices[4].Position.y = (m_lengthy / 2.0f);
	m_vertices[4].Position.z = (m_lengthz / 2.0f);

	m_vertices[5].Position.x = (m_lengthx / 2.0f);
	m_vertices[5].Position.y = (m_lengthy / 2.0f);
	m_vertices[5].Position.z = (m_lengthz / 2.0f);

	m_vertices[6].Position.x = (m_lengthx / 2.0f);
	m_vertices[6].Position.y = -(m_lengthy / 2.0f);
	m_vertices[6].Position.z = (m_lengthz / 2.0f);

	m_vertices[7].Position.x = -(m_lengthx / 2.0f);
	m_vertices[7].Position.y = -(m_lengthy / 2.0f);
	m_vertices[7].Position.z = (m_lengthz / 2.0f);


	// UV���W��ݒ�
	  // �O��
	m_vertices[0].TexCoord = { 0.0f, 0.0f };
	m_vertices[1].TexCoord = { 1.0f, 0.0f };
	m_vertices[2].TexCoord = { 1.0f, 1.0f };
	m_vertices[3].TexCoord = { 0.0f, 1.0f };

	// �w��
	m_vertices[4].TexCoord = { 0.0f, 0.0f };
	m_vertices[5].TexCoord = { 1.0f, 0.0f };
	m_vertices[6].TexCoord = { 1.0f, 1.0f };
	m_vertices[7].TexCoord = { 0.0f, 1.0f };

	// �E��
	m_vertices[1].TexCoord = { 0.0f, 0.0f };
	m_vertices[5].TexCoord = { 1.0f, 0.0f };
	m_vertices[6].TexCoord = { 1.0f, 1.0f };
	m_vertices[2].TexCoord = { 0.0f, 1.0f };

	// ����
	m_vertices[0].TexCoord = { 0.0f, 0.0f };
	m_vertices[4].TexCoord = { 1.0f, 0.0f };
	m_vertices[7].TexCoord = { 1.0f, 1.0f };
	m_vertices[3].TexCoord = { 0.0f, 1.0f };

	// ���
	m_vertices[4].TexCoord = { 0.0f, 0.0f };
	m_vertices[5].TexCoord = { 1.0f, 0.0f };
	m_vertices[1].TexCoord = { 1.0f, 1.0f };
	m_vertices[0].TexCoord = { 0.0f, 1.0f };

	// ����
	m_vertices[3].TexCoord = { 0.0f, 0.0f };
	m_vertices[2].TexCoord = { 1.0f, 0.0f };
	m_vertices[6].TexCoord = { 1.0f, 1.0f };
	m_vertices[7].TexCoord = { 0.0f, 1.0f };

	for (int i = 0; i < 8; i++) {
		// ���_�J���[�ݒ�
		m_vertices[i].Diffuse = m_color;
		// �m�[�}���C�Y
		Normalize(
			m_vertices[i].Position,
			m_vertices[i].Normal);
	}
}

// �C���f�b�N�X����
void BoxMesh::CreateIndex() {


	// �C���f�b�N�X�f�[�^�N���A
	m_indices.clear();

	// �C���f�b�N�X�𐶐�
	FACE faces[12];

	faces[0].idx[0] = 0;		// ��O  ok
	faces[0].idx[1] = 1;
	faces[0].idx[2] = 2;

	faces[1].idx[0] = 0;
	faces[1].idx[1] = 2;
	faces[1].idx[2] = 3;

	faces[2].idx[0] = 5;		// ��  ok
	faces[2].idx[1] = 4;
	faces[2].idx[2] = 7;

	faces[3].idx[0] = 5;
	faces[3].idx[1] = 7;
	faces[3].idx[2] = 6;

	faces[4].idx[0] = 4;		// ���� ok
	faces[4].idx[1] = 0;
	faces[4].idx[2] = 7;

	faces[5].idx[0] = 0;
	faces[5].idx[1] = 3;
	faces[5].idx[2] = 7;

	faces[6].idx[0] = 1;		// �E�� ok
	faces[6].idx[1] = 5;
	faces[6].idx[2] = 6;

	faces[7].idx[0] = 1;
	faces[7].idx[1] = 6;
	faces[7].idx[2] = 2;

	faces[8].idx[0] = 0;		// �㑤 ok
	faces[8].idx[1] = 4;
	faces[8].idx[2] = 1;

	faces[9].idx[0] = 4;
	faces[9].idx[1] = 5;
	faces[9].idx[2] = 1;

	faces[10].idx[0] = 7;		// ����
	faces[10].idx[1] = 3;
	faces[10].idx[2] = 2;

	faces[11].idx[0] = 7;
	faces[11].idx[1] = 2;
	faces[11].idx[2] = 6;

	// �C���f�b�N�X�o�^
	for (int i = 0; i < 12; i++) {
		m_indices.emplace_back(faces[i].idx[0]);
		m_indices.emplace_back(faces[i].idx[1]);
		m_indices.emplace_back(faces[i].idx[2]);
	}
}
