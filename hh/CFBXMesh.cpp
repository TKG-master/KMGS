#include "CFBXMesh.h"
#include <iostream>
using namespace DirectX::SimpleMath;

FBXMesh::FBXMesh()
{

}

FBXMesh::~FBXMesh()
{

}

void FBXMesh::Init()
{
	// ���b�V���ǂݍ���
	CStaticMesh staticmesh;

	std::vector<std::string> filename =
	{
		"assets/model/book",
	};

	std::vector<std::string> texdirectory =
	{
		"assets/model/book"
	};

	// u8string��string�ɕϊ�
	std::u8string u8str = u8"assets/model/book/book.obj";  //ok
	//std::u8string u8str = u8"assets/model/�O�����q���M��1.0/�O�����q���M��1.0.pmx";   //ng

	std::string str(reinterpret_cast<const char*>(u8str.c_str()), u8str.size());

	staticmesh.Load(str, texdirectory[0]);

	g_MeshRenderer.Init(staticmesh);

	// �V�F�[�_�I�u�W�F�N�g����
	g_Shader.Create("shader/vertexLightingVS.hlsl", "shader/vertexLightingPS.hlsl");

	// �T�u�Z�b�g���擾
	g_subsets = staticmesh.GetSubsets();

	// diffuse�e�N�X�`�����擾
	g_DiffuseTextures = staticmesh.GetDiffuseTextures();

	// �}�e���A�����擾	
	std::vector<MATERIAL> materials = staticmesh.GetMaterials();

	// �}�e���A���������[�v
	for (int i = 0; i < materials.size(); i++)
	{
		// �}�e���A���I�u�W�F�N�g����
		std::unique_ptr<CMaterial> m = std::make_unique<CMaterial>();

		// �}�e���A�������Z�b�g
		m->Create(materials[i]);

		// �}�e���A���I�u�W�F�N�g��z��ɒǉ�
		g_Materiales.push_back(std::move(m));
	}
}

void FBXMesh::UnInit()
{

}

void FBXMesh::Draw()
{
	Matrix rmtx = Matrix::CreateFromYawPitchRoll(rot.y, rot.x, rot.z);
	Matrix smtx = Matrix::CreateScale(scale.x, scale.y, scale.z);
	Matrix tmtx = Matrix::CreateTranslation(pos.x, pos.y, pos.z);

	Matrix wmtx = smtx * rmtx * tmtx;

	Renderer::SetWorldMatrix(&wmtx);

	g_Shader.SetGPU();

	// �C���f�b�N�X�o�b�t�@�E���_�o�b�t�@���Z�b�g
	g_MeshRenderer.BeforeDraw();

	// �}�e���A���������[�v 
	for (int i = 0; i < g_subsets.size(); i++)
	{
		// �}�e���A�����Z�b�g(�T�u�Z�b�g���̒��ɂ���}�e���A���C���f�b�N���g�p����)
		g_Materiales[g_subsets[i].MaterialIdx]->SetGPU();

		if (g_Materiales[g_subsets[i].MaterialIdx]->isDiffuseTextureEnable())
		{
			g_DiffuseTextures[g_subsets[i].MaterialIdx]->SetGPU();
		}

		g_MeshRenderer.DrawSubset(
			g_subsets[i].IndexNum,							// �`�悷��C���f�b�N�X��
			g_subsets[i].IndexBase,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu	
			g_subsets[i].VertexBase);						// ���_�o�b�t�@�̍ŏ�����g�p
	}
}
