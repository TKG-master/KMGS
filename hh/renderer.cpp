#include "renderer.h"
#include "Application.h"
#define SAFE_RELEASE(p)       { if( NULL != p ) { p->Release(); p = NULL; } }
using namespace DirectX::SimpleMath;

D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device* Renderer::m_Device{};
ID3D11DeviceContext* Renderer::m_DeviceContext{};
IDXGISwapChain* Renderer::m_SwapChain{};
ID3D11RenderTargetView* Renderer::m_RenderTargetView{};
ID3D11DepthStencilView* Renderer::m_DepthStencilView{};
ID3D11SamplerState* Renderer::m_samplerState{};
ID3D11RasterizerState* Renderer::m_rsCullModeFront;
ID3D11RasterizerState* Renderer::m_rsCullModeBack;



ID3D11Buffer* Renderer::m_WorldBuffer{};
ID3D11Buffer* Renderer::m_ViewBuffer{};
ID3D11Buffer* Renderer::m_ProjectionBuffer{};
ID3D11Buffer* Renderer::m_LightViewBuffer{};
ID3D11Buffer* Renderer::m_LightProjectionBuffer{};


ID3D11Buffer* Renderer::m_MaterialBuffer{};
ID3D11Buffer* Renderer::m_LightBuffer{};


ID3D11DepthStencilState* Renderer::m_DepthStateEnable{};
ID3D11DepthStencilState* Renderer::m_DepthStateDisable{};


ID3D11BlendState* Renderer::m_BlendState[MAX_BLENDSTATE];
ID3D11BlendState* Renderer::m_BlendStateATC{};

ID3D11Texture2D* Renderer::m_depthStencile{};
ID3D11Texture2D* Renderer::m_WipedepthStencile{};
D3D11_TEXTURE2D_DESC Renderer::textureDesc{};
ID3D11Texture2D* Renderer::m_renderTarget{};

DirectX::SimpleMath::Matrix Renderer::m_view{};

void Renderer::Init()
{
	HRESULT hr = S_OK;
	UINT flag = 0;


#ifdef _DEBUG
	flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // _DEBUG

	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = Application::GetWidth();
	swapChainDesc.BufferDesc.Height = Application::GetHeight();
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = Application::GetWindow();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		flag,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		&m_SwapChain,
		&m_Device,
		&m_FeatureLevel,
		&m_DeviceContext);




	// レンダーターゲットビュー作成
	m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_renderTarget);
	m_Device->CreateRenderTargetView(m_renderTarget, NULL, &m_RenderTargetView);


	// デプスステンシルバッファ作成
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &m_depthStencile);

	// デプスステンシルバッファ作成
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	m_Device->CreateTexture2D(&textureDesc, NULL, &m_WipedepthStencile);

	CreateDepthStencli(&m_DepthStencilView, m_depthStencile);

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	// ビューポート設定
	D3D11_VIEWPORT viewport;
	viewport.Width = (FLOAT)Application::GetWidth();
	viewport.Height = (FLOAT)Application::GetHeight();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	m_DeviceContext->RSSetViewports(1, &viewport);


	// ラスタライザステート設定CullModeBack版
	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	//	rasterizerDesc.FillMode = D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	//rasterizerDesc.CullMode = D3D11_CULL_NONE;
	//rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.MultisampleEnable = FALSE;

	m_Device->CreateRasterizerState(&rasterizerDesc, &m_rsCullModeBack);

	//CullModeFront版も設定
	rasterizerDesc.CullMode = D3D11_CULL_FRONT;
	//rasterizerDesc.CullMode = D3D11_CULL_NONE;

	m_Device->CreateRasterizerState(&rasterizerDesc, &m_rsCullModeFront);
	//デフォルトはBackをセット
	m_DeviceContext->RSSetState(m_rsCullModeBack);

	// ブレンド ステート生成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = FALSE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[0]);

	// ブレンド ステート生成 (アルファ ブレンド用)
	//BlendDesc.AlphaToCoverageEnable = TRUE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[1]);

	// ブレンド ステート生成 (加算合成用)
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[2]);

	// ブレンド ステート生成 (減算合成用)
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_REV_SUBTRACT;
	m_Device->CreateBlendState(&BlendDesc, &m_BlendState[3]);

	SetBlendState(BS_ALPHABLEND);

	// デプスステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateEnable);//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	m_Device->CreateDepthStencilState(&depthStencilDesc, &m_DepthStateDisable);//深度無効ステート

	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc{};
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MaxAnisotropy = 4;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	m_Device->CreateSamplerState(&samplerDesc, &m_samplerState);

	m_DeviceContext->PSSetSamplers(0, 1, &m_samplerState);



	// 定数バッファ生成
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.ByteWidth = sizeof(Matrix);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = sizeof(float);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_WorldBuffer);
	m_DeviceContext->VSSetConstantBuffers(0, 1, &m_WorldBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_ProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_ProjectionBuffer);


	bufferDesc.ByteWidth = sizeof(MATERIAL);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_MaterialBuffer);
	m_DeviceContext->VSSetConstantBuffers(3, 1, &m_MaterialBuffer);
	m_DeviceContext->PSSetConstantBuffers(3, 1, &m_MaterialBuffer);


	bufferDesc.ByteWidth = sizeof(LIGHT);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightBuffer);
	m_DeviceContext->VSSetConstantBuffers(4, 1, &m_LightBuffer);
	m_DeviceContext->PSSetConstantBuffers(4, 1, &m_LightBuffer);


	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightViewBuffer);
	m_DeviceContext->VSSetConstantBuffers(6, 1, &m_LightViewBuffer);

	m_Device->CreateBuffer(&bufferDesc, NULL, &m_LightProjectionBuffer);
	m_DeviceContext->VSSetConstantBuffers(7, 1, &m_LightProjectionBuffer);


	// ライト初期化
	LIGHT light{};
	light.Enable = true;
	light.Position = {};
	light.Direction = Vector4(0.5f, -1.0f, 0.8f, 0.0f);
	light.Direction.Normalize();
	light.Ambient = Color(1.0f, 1.2f, 0.2f, 1.0f);
	light.Diffuse = Color(3.5f, 1.5f, 1.5f, 1.0f);
	SetLight(&light);



	// マテリアル初期化
	MATERIAL material{};
	material.Diffuse = Color(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = Color(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);



}

void Renderer::Uninit()
{
#if 1
	if (m_DeviceContext) {
		m_DeviceContext->ClearState();
		//	m_DeviceContext->Release();
	}


	SAFE_RELEASE(m_WorldBuffer);
	SAFE_RELEASE(m_ViewBuffer);
	SAFE_RELEASE(m_ProjectionBuffer);
	SAFE_RELEASE(m_LightBuffer);
	SAFE_RELEASE(m_MaterialBuffer);
	SAFE_RELEASE(m_LightViewBuffer);
	SAFE_RELEASE(m_LightProjectionBuffer);

	SAFE_RELEASE(m_samplerState);
	SAFE_RELEASE(m_DepthStateEnable);
	SAFE_RELEASE(m_DepthStateDisable);
	SAFE_RELEASE(m_rsCullModeBack);
	SAFE_RELEASE(m_rsCullModeFront);

	for (int Index = 0; Index < MAX_BLENDSTATE; Index++) {
		SAFE_RELEASE(m_BlendState[Index]);
	}
	SAFE_RELEASE(m_BlendStateATC);

	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_renderTarget);
	SAFE_RELEASE(m_depthStencile);
	SAFE_RELEASE(m_WipedepthStencile);

	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_DeviceContext);
	SAFE_RELEASE(m_Device);
#else
	SAFE_RELEASE(m_WorldBuffer);
	SAFE_RELEASE(m_ViewBuffer);
	SAFE_RELEASE(m_ProjectionBuffer);
	SAFE_RELEASE(m_LightBuffer);
	SAFE_RELEASE(m_MaterialBuffer);
	SAFE_RELEASE(m_WipeBuffer);
	SAFE_RELEASE(m_CameraPosBuffer);
	SAFE_RELEASE(m_PlayerPosBuffer);
	SAFE_RELEASE(m_TimeBuffer);
	SAFE_RELEASE(m_FrgBuffer);
	SAFE_RELEASE(m_LightViewBuffer);
	SAFE_RELEASE(m_LightProjectionBuffer);


	SAFE_RELEASE(m_samplerState)

		m_DeviceContext->ClearState();
	SAFE_RELEASE(m_RenderTargetView);
	SAFE_RELEASE(m_SwapChain);
	SAFE_RELEASE(m_DeviceContext);
	SAFE_RELEASE(m_Device);
	SAFE_RELEASE(m_DepthStencilView);
	SAFE_RELEASE(m_rsCullModeBack);
	SAFE_RELEASE(m_rsCullModeFront);

	SAFE_RELEASE(m_DepthStateEnable);
	SAFE_RELEASE(m_DepthStateDisable);
	for (int Index = 0; Index < MAX_BLENDSTATE; Index++)
	{
		SAFE_RELEASE(m_BlendState[Index]);
	}
	SAFE_RELEASE(m_BlendStateATC);
	SAFE_RELEASE(m_renderTarget);
	SAFE_RELEASE(m_depthStencile);
	SAFE_RELEASE(m_WipedepthStencile);

#endif

}

void Renderer::Begin()
{
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };


	// スロット数に応じてリソースを解除する
	constexpr UINT kMaxTextureSlots = D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT;

	// スロット数分の null ポインタ配列を作成
	ID3D11ShaderResourceView* nullSRVs[kMaxTextureSlots] = { nullptr };

	// ピクセルシェーダーの全スロットに null を設定
	m_DeviceContext->PSSetShaderResources(0, kMaxTextureSlots, nullSRVs);
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, clearColor);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, 0);
}

void Renderer::End()
{
	m_SwapChain->Present(1, 0);
}

void Renderer::SetDepthEnable(bool Enable)
{
	if (Enable)
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateEnable, NULL);
	else
		m_DeviceContext->OMSetDepthStencilState(m_DepthStateDisable, NULL);

}

void Renderer::SetATCEnable(bool Enable)
{
	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	if (Enable)
		m_DeviceContext->OMSetBlendState(m_BlendStateATC, blendFactor, 0xffffffff);
	else
		m_DeviceContext->OMSetBlendState(m_BlendState[0], blendFactor, 0xffffffff);

}

void Renderer::SetWorldViewProjection2D()
{
	Matrix world;
	world = Matrix::Identity;			// 単位行列にする
	world = world.Transpose();			// 転置
	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);

	Matrix view;
	view = Matrix::Identity;			// 単位行列にする
	view = view.Transpose();			// 転置
	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);

	Matrix projection;

	// 2D描画を左上原点にする  (20230512 update by tomoki.suzuki　
	projection = DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,
		static_cast<float>(Application::GetWidth()),		// ビューボリュームの最小Ｘ
		static_cast<float>(Application::GetHeight()),		// ビューボリュームの最小Ｙ
		0.0f,												// ビューボリュームの最大Ｙ
		0.0f,
		1.0f);

	projection = projection.Transpose();

	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}


void Renderer::SetWorldMatrix(Matrix* WorldMatrix)
{
	Matrix world;
	world = WorldMatrix->Transpose();					// 転置

	m_DeviceContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix(Matrix* ViewMatrix)
{
	Matrix view;
	view = ViewMatrix->Transpose();

	m_view = *ViewMatrix;					// 転置


	m_DeviceContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}
DirectX::SimpleMath::Matrix Renderer::GetViewMatrix()
{
	return m_view;
}

void Renderer::SetLightViewMatrix(Matrix* ViewMatrix)
{
	Matrix view;
	view = ViewMatrix->Transpose();						// 転置

	m_DeviceContext->UpdateSubresource(m_LightViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix(Matrix* ProjectionMatrix)
{
	Matrix projection;
	projection = ProjectionMatrix->Transpose();

	m_DeviceContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}
void Renderer::SetLightProjectionMatrix(Matrix* ProjectionMatrix)
{
	Matrix projection;
	projection = ProjectionMatrix->Transpose();

	m_DeviceContext->UpdateSubresource(m_LightProjectionBuffer, 0, NULL, &projection, 0, 0);
}

void Renderer::SetMaterial(MATERIAL Material)
{
	m_DeviceContext->UpdateSubresource(m_MaterialBuffer, 0, NULL, &Material, 0, 0);
}

void Renderer::SetLight(void* Light)
{
	m_DeviceContext->UpdateSubresource(m_LightBuffer, 0, NULL, Light, 0, 0);
}


//void Renderer::CreateDepthStencli(ID3D11DepthStencilView** _DepthStencilView)
//{
//	// デプスステンシルビュー作成
//	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
//	depthStencilViewDesc.Format = textureDesc.Format;
//	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
//	depthStencilViewDesc.Flags = 0;
//	m_Device->CreateDepthStencilView(m_depthStencile, &depthStencilViewDesc, _DepthStencilView);
//
//}

void Renderer::CreateDepthStencli(ID3D11DepthStencilView** _DepthStencilView, ID3D11Texture2D* _Depth)
{
	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc{};
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	m_Device->CreateDepthStencilView(_Depth, &depthStencilViewDesc, _DepthStencilView);

}

void Renderer::CreateRenderTargetView(ID3D11RenderTargetView** _TargetView, ID3D11Texture2D** _ptex, ID3D11ShaderResourceView** _SRV)
{
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	desc.Width = Application::GetWidth();
	desc.Height = Application::GetHeight();
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;

	HRESULT hr = GetDevice()->CreateTexture2D(&desc, nullptr, _ptex);
	if (FAILED(hr)) {
		// エラーハンドリング
	}

	// シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = desc.Format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	hr = GetDevice()->CreateShaderResourceView(*_ptex, &srvDesc, _SRV);
	if (FAILED(hr)) {
		// エラーハンドリング
	}

	// レンダーターゲットビューの作成
	hr = GetDevice()->CreateRenderTargetView(*_ptex, NULL, _TargetView);
	if (FAILED(hr)) {
		// エラーハンドリング
	}
}

ID3D11RenderTargetView* Renderer::GetRenderTargetView()
{
	return m_RenderTargetView;
}

ID3D11DepthStencilView* Renderer::GetDepthStencli()
{
	return m_DepthStencilView;
}

void Renderer::SetRenderTargets(UINT num, ID3D11RenderTargetView* ppViews, ID3D11DepthStencilView* pView)
{
	static ID3D11RenderTargetView* rtvs[4];

	if (num > 4) num = 4;
	for (UINT i = 0; i < num; ++i)
		rtvs[i] = &ppViews[i];
	m_DeviceContext->OMSetRenderTargets(num, rtvs, pView ? pView : nullptr);

	// ビューポートの設定
	D3D11_VIEWPORT vp;
	vp.TopLeftX = 0.0f;
	vp.TopLeftY = 0.0f;
	vp.Width = (float)Application::GetWidth();
	vp.Height = (float)Application::GetHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	m_DeviceContext->RSSetViewports(1, &vp);
}

void Renderer::CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName)
{

	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreateVertexShader(buffer, fsize, NULL, VertexShader);


	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	0,		D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT,		0,	4 * 3,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	4 * 6,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,			0,	4 * 10, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);

	m_Device->CreateInputLayout(layout,
		numElements,
		buffer,
		fsize,
		VertexLayout);

	delete[] buffer;
}

void Renderer::CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName)
{
	FILE* file;
	long int fsize;

	fopen_s(&file, FileName, "rb");
	assert(file);

	fsize = _filelength(_fileno(file));
	unsigned char* buffer = new unsigned char[fsize];
	fread(buffer, fsize, 1, file);
	fclose(file);

	m_Device->CreatePixelShader(buffer, fsize, NULL, PixelShader);

	delete[] buffer;

}

void Renderer::SetCullMode(CULLMODE _Cull)
{
	switch (_Cull)
	{
	case FRONT:
		m_DeviceContext->RSSetState(m_rsCullModeFront);
		break;
	case BACK:
		m_DeviceContext->RSSetState(m_rsCullModeBack);
		break;
	default:
		break;
	}
}
