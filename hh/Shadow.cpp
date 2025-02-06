#include "Shadow.h"
#define SAFE_RELEASE(p)       { if( NULL != p ) { p->Release(); p = NULL; } }

void Shadow::Init()
{

	Renderer::CreateDepthStencli(&m_DSV);
	Renderer::CreateRenderTargetView(&m_RTV, &m_pTex, &m_shaderResourceView);
	m_Shader.Create("shader/unlitTextureVS.hlsl", "shader/PS_Shadow.hlsl");

}

void Shadow::Begin()
{
	float clearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	ID3D11DeviceContext* Context = Renderer::GetDeviceContext();

	//���C�v�p��RTV��DSV�̍쐬
	// �X���b�g���ɉ����ă��\�[�X����������
	constexpr UINT kMaxTextureSlots = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

	// �X���b�g������ null �|�C���^�z����쐬
	ID3D11ShaderResourceView* nullSRVs[kMaxTextureSlots] = { nullptr };

	// �s�N�Z���V�F�[�_�[�̑S�X���b�g�� null ��ݒ�
	Context->PSSetShaderResources(0, kMaxTextureSlots, nullSRVs);


	Context->ClearRenderTargetView(m_RTV, clearColor);
	Context->ClearDepthStencilView(m_DSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	Renderer::SetRenderTargets(1, m_RTV, nullptr);

}

void Shadow::End()
{
	ID3D11RenderTargetView* RTV = Renderer::GetRenderTargetView();
	ID3D11DepthStencilView* DSV = Renderer::GetDepthStencli();

	Renderer::SetRenderTargets(1, RTV, DSV);
	ID3D11DeviceContext* Context = Renderer::GetDeviceContext();
	m_Shader.SetGPU();
	Context->PSSetShaderResources(2, 1, &m_shaderResourceView);


}

void Shadow::Draw()
{
}

void Shadow::UnInit()
{
	SAFE_RELEASE(m_DSV);
	SAFE_RELEASE(m_RTV);
	SAFE_RELEASE(m_shaderResourceView);
	SAFE_RELEASE(m_pTex);
}