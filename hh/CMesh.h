#pragma once
#include	<vector>
#include	<SimpleMath.h>
#include	<simplemath.h>
#include	"renderer.h"

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "CShader.h"
#include "CMaterial.h"
#include "CTexture.h"
class CMesh {
protected:
	std::vector<VERTEX_3D>		m_vertices;		// ���_���W�Q
	std::vector<unsigned int>	m_indices;		// �C���f�b�N�X�f�[�^�Q

	CVertexBuffer<VERTEX_3D>	m_VertexBuffer;		//���_�o�b�t�@
	CIndexBuffer				m_IndexBuffer;		//�C���f�b�N�X�o�b�t�@
	CShader					m_Shader;			//�V�F�[�_�[
	CMaterial				m_Material;			//�}�e���A��
	CTexture					m_Texture;			//�e�N�X�`��

	DirectX::SimpleMath::Matrix worldmtx;		// ���[���h�}�g���b�N�X

	// SRT���
	DirectX::SimpleMath::Vector3 m_Position = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Rotation = { 0,0,0 };
	DirectX::SimpleMath::Vector3 m_Scale = { 1.0f,1.0f,1.0f };
public:


	// ���_�f�[�^�擾
	const std::vector<VERTEX_3D>& GetVertices() { return m_vertices; }
	// �C���f�b�N�X�f�[�^�擾
	const std::vector<unsigned int>& GetIndices() { return m_indices; }
	// ���_�o�b�t�@���X�V
	void Modify(const std::vector<VERTEX_3D>& vertices) { m_VertexBuffer.Modify(vertices); }

	void SetPosition(DirectX::SimpleMath::Vector3 pos) { m_Position = pos; };
	DirectX::SimpleMath::Vector3 GetPosition() { return m_Position; };

	void SetRotation(DirectX::SimpleMath::Vector3 rot) { m_Rotation = rot; };
	DirectX::SimpleMath::Vector3 GetRotation() { return m_Rotation; };

	void SetScale(DirectX::SimpleMath::Vector3 pos) { m_Scale = pos; };
	DirectX::SimpleMath::Vector3 GetScale() { return m_Scale; };


	//��]��Ɏg�p�F�p�x�̏C��
	void ModifyRotation();

	// ������
	virtual void Init();
	// �X�V
	virtual void Update();
	// �`��
	virtual void Draw();
	// �T�u�Z�b�g�`��
	virtual void DrawSubset(unsigned int indexnum, unsigned int baseindex, unsigned int basevertexindex);

};

