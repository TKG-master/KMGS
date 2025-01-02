#pragma once
#include	<SimpleMath.h>
#include	<memory>
#include	"CMeshRenderer.h"
#include	"CMaterial.h"
#include	"CShader.h"
#include	"CTexture.h"
#include	"CStaticMesh.h"
#include	"utility.h"

class FBXMesh
{
private:
	CMeshRenderer g_MeshRenderer;
	std::vector<std::unique_ptr<CMaterial>> g_Materiales;
	CShader	g_Shader;
	std::vector<SUBSET> g_subsets;

	std::vector<std::unique_ptr<CTexture>> g_Textures;

	std::vector<std::unique_ptr<CTexture>> g_DiffuseTextures;

	DirectX::SimpleMath::Vector3 pos;
	DirectX::SimpleMath::Vector3 scale;
	DirectX::SimpleMath::Vector3 rot;

public:
	FBXMesh();
	~FBXMesh();

	void Init();
	void UnInit();

	void Draw();

	void Setpos(DirectX::SimpleMath::Vector3 position) { this->pos = position; };
	DirectX::SimpleMath::Vector3 Getpos() { return this->pos; };

	void Setscale(DirectX::SimpleMath::Vector3 sca) { this->scale = sca; };
	DirectX::SimpleMath::Vector3 Getscale() { return this->scale; };

	void Setrot(DirectX::SimpleMath::Vector3 rot) { this->rot = rot; };
	DirectX::SimpleMath::Vector3 Getrot() { return this->rot; };




};

