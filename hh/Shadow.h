#pragma once
#include "renderer.h"
#include "CShader.h"
class Shadow
{
public:
	Shadow() {}
	virtual ~Shadow()
	{
		UnInit();
	}
	void Init();
	void Begin();
	void End();
	void Draw();
	void UnInit();
private:
	CShader	m_Shader;

	ID3D11RenderTargetView* m_RTV = nullptr;
	ID3D11DepthStencilView* m_DSV = nullptr;
	ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
	ID3D11Texture2D* m_pTex = nullptr;

};

