#include "Scene.h"

CScene::CScene() {
}

CScene::~CScene() {
}

bool CScene::Prcs_Msg_Mouse(HWND hWnd, UINT nMsg_ID, WPARAM wParam, LPARAM lParam) {
	return false;
}

bool CScene::Prcs_Msg_Keyboard(HWND hWnd, UINT nMsg_ID, WPARAM wParam, LPARAM lParam) {
	return false;
}

ID3D12RootSignature* CScene::Crt_Graphics_RootSignature(ID3D12Device* pd3d_Device) {
	ID3D12RootSignature* pd3d_Graphics_RootSignature = NULL;

	D3D12_ROOT_SIGNATURE_DESC d3d_RootSignature_Desc;
	ZeroMemory(&d3d_RootSignature_Desc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3d_RootSignature_Desc.NumParameters = 0;
	d3d_RootSignature_Desc.pParameters = NULL;
	d3d_RootSignature_Desc.NumStaticSamplers = 0;
	d3d_RootSignature_Desc.pStaticSamplers = NULL;
	d3d_RootSignature_Desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

	HRESULT hResult;
	ID3DBlob* pd3d_Signature_Blob = NULL;
	ID3DBlob* pd3d_Error_Blob = NULL;

	hResult = D3D12SerializeRootSignature(&d3d_RootSignature_Desc, D3D_ROOT_SIGNATURE_VERSION_1, &pd3d_Signature_Blob, &pd3d_Error_Blob);
	pd3d_Device->CreateRootSignature(0, pd3d_Signature_Blob->GetBufferPointer(), pd3d_Signature_Blob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void**)&pd3d_Graphics_RootSignature);

	// print error
	if (FAILED(hResult)) {
		OutputDebugStringA(static_cast<const char*>(pd3d_Error_Blob->GetBufferPointer()));
	}

	if (pd3d_Signature_Blob) {
		pd3d_Signature_Blob->Release();
	}
	if (pd3d_Error_Blob) {
		pd3d_Error_Blob->Release();
	}

	return pd3d_Graphics_RootSignature;
}

ID3D12RootSignature* CScene::Get_Graphics_RootSignature() {	// unused
	return m_pd3d_Graphics_RootSignature;
}

//void CScene::Crt_Graphics_Pipeline_State(ID3D12Device* pd3d_Device) {	//unused
//	ID3DBlob* pd3d_Vertex_Shader_Blob = NULL;
//	ID3DBlob* pd3d_Pixel_Shader_Blob = NULL;
//
//	UINT nCompile_Flags = 0;
//#if defined(_DEBUG)
//	nCompile_Flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
//#endif
//
//	HRESULT hResult;
//	ID3DBlob* pd3d_Error_Blob;
//
//	hResult = D3DCompileFromFile(L"Shaders.hlsl", NULL, NULL, "VSMain", "vs_5_1", nCompile_Flags, 0, &pd3d_Vertex_Shader_Blob, &pd3d_Error_Blob);
//	D3DCompileFromFile(L"Shaders.hlsl", NULL, NULL, "PSMain", "ps_5_1", nCompile_Flags, 0, &pd3d_Pixel_Shader_Blob, NULL);
//
//	// print error
//	if (FAILED(hResult)) {
//		OutputDebugStringA(static_cast<const char*>(pd3d_Error_Blob->GetBufferPointer()));
//	}
//
//	if (pd3d_Error_Blob) {
//		pd3d_Error_Blob->Release();
//	}
//
//	D3D12_RASTERIZER_DESC d3d_Rasterizer_Desc;
//	ZeroMemory(&d3d_Rasterizer_Desc, sizeof(D3D12_RASTERIZER_DESC));
//	d3d_Rasterizer_Desc.FillMode = D3D12_FILL_MODE_SOLID;
//	d3d_Rasterizer_Desc.CullMode = D3D12_CULL_MODE_BACK;
//	d3d_Rasterizer_Desc.FrontCounterClockwise = FALSE;
//	d3d_Rasterizer_Desc.DepthBias = 0;
//	d3d_Rasterizer_Desc.DepthBiasClamp = 0.0f;
//	d3d_Rasterizer_Desc.SlopeScaledDepthBias = 0.0f;
//	d3d_Rasterizer_Desc.DepthClipEnable = TRUE;
//	d3d_Rasterizer_Desc.MultisampleEnable = FALSE;
//	d3d_Rasterizer_Desc.AntialiasedLineEnable = FALSE;
//	d3d_Rasterizer_Desc.ForcedSampleCount = 0;
//	d3d_Rasterizer_Desc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
//
//	D3D12_BLEND_DESC d3d_Blend_Desc;
//	ZeroMemory(&d3d_Blend_Desc, sizeof(D3D12_BLEND_DESC));
//	d3d_Blend_Desc.AlphaToCoverageEnable = FALSE;
//	d3d_Blend_Desc.IndependentBlendEnable = FALSE;
//	d3d_Blend_Desc.RenderTarget[0].BlendEnable = FALSE;
//	d3d_Blend_Desc.RenderTarget[0].LogicOpEnable = FALSE;
//	d3d_Blend_Desc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
//	d3d_Blend_Desc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
//	d3d_Blend_Desc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
//	d3d_Blend_Desc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
//	d3d_Blend_Desc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
//	d3d_Blend_Desc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
//	d3d_Blend_Desc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
//	d3d_Blend_Desc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
//
//	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3d_Pipeline_State_Desc;
//	ZeroMemory(&d3d_Pipeline_State_Desc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
//	d3d_Pipeline_State_Desc.pRootSignature = m_pd3d_Graphics_RootSignature;
//	d3d_Pipeline_State_Desc.VS.pShaderBytecode = pd3d_Vertex_Shader_Blob->GetBufferPointer();
//	d3d_Pipeline_State_Desc.VS.BytecodeLength = pd3d_Vertex_Shader_Blob->GetBufferSize();
//	d3d_Pipeline_State_Desc.PS.pShaderBytecode = pd3d_Pixel_Shader_Blob->GetBufferPointer();
//	d3d_Pipeline_State_Desc.PS.BytecodeLength = pd3d_Pixel_Shader_Blob->GetBufferSize();
//	d3d_Pipeline_State_Desc.RasterizerState = d3d_Rasterizer_Desc;
//	d3d_Pipeline_State_Desc.BlendState = d3d_Blend_Desc;
//	d3d_Pipeline_State_Desc.DepthStencilState.DepthEnable = FALSE;
//	d3d_Pipeline_State_Desc.DepthStencilState.StencilEnable = FALSE;
//	d3d_Pipeline_State_Desc.InputLayout.pInputElementDescs = NULL;
//	d3d_Pipeline_State_Desc.InputLayout.NumElements = 0;
//	d3d_Pipeline_State_Desc.SampleMask = UINT_MAX;
//	d3d_Pipeline_State_Desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
//	d3d_Pipeline_State_Desc.NumRenderTargets = 1;
//	d3d_Pipeline_State_Desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
//	d3d_Pipeline_State_Desc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
//	d3d_Pipeline_State_Desc.SampleDesc.Count = 1;
//	d3d_Pipeline_State_Desc.SampleDesc.Quality = 0;
//	pd3d_Device->CreateGraphicsPipelineState(&d3d_Pipeline_State_Desc, __uuidof(ID3D12PipelineState), (void**)&m_pd3d_Graphics_Pipeline_State);
//
//	if (pd3d_Vertex_Shader_Blob) {
//		pd3d_Vertex_Shader_Blob->Release();
//	}
//	if (pd3d_Pixel_Shader_Blob) {
//		pd3d_Pixel_Shader_Blob->Release();
//	}
//}

void CScene::Build_Objects(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List) {
	m_pd3d_Graphics_RootSignature = Crt_Graphics_RootSignature(pd3d_Device);

	m_nShaders = 1;
	m_ppShaders = new CShader * [m_nShaders];

	CShader* pShader = new CShader();
	pShader->Crt_Shader(pd3d_Device, m_pd3d_Graphics_RootSignature);
	pShader->Build_Objects(pd3d_Device, pd3d_Command_List);

	m_ppShaders[0] = pShader;
}

void CScene::Release_Objects() {
	if (m_pd3d_Graphics_RootSignature) {
		m_pd3d_Graphics_RootSignature->Release();
	}

	if (m_ppShaders) {
		for (int i = 0; i < m_nShaders; ++i) {
			m_ppShaders[i]->Release_Shader_Variables();
			m_ppShaders[i]->Release_Objects();
			m_ppShaders[i]->Release();
		}

		delete[] m_ppShaders;
	}
}

bool CScene::Prcs_Input() {
	return false;
}

void CScene::Anim_Objects(float fElapsed_Time) {
	for (int i = 0; i < m_nShaders; ++i) {
		m_ppShaders[i]->Anim_Objects(fElapsed_Time);
	}
}

//void CScene::Prepare_Render(ID3D12GraphicsCommandList* pd3d_Command_List) {	// unused
//	pd3d_Command_List->SetGraphicsRootSignature(m_pd3d_Graphics_RootSignature);
//	pd3d_Command_List->SetPipelineState(m_pd3d_Graphics_Pipeline_State);
//	pd3d_Command_List->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
//}

void CScene::Render(ID3D12GraphicsCommandList* pd3d_Command_List) {
	pd3d_Command_List->SetGraphicsRootSignature(m_pd3d_Graphics_RootSignature);

	for (int i = 0; i < m_nShaders; ++i) {
		m_ppShaders[i]->Render(pd3d_Command_List);
	}
}

void CScene::Release_Upload_Buffers() {
	if (m_ppShaders) {
		for (int i = 0; i < m_nShaders; ++i) {
			if (m_ppShaders[i]) {
				m_ppShaders[i]->Release_Upload_Buffers();
			}
		}
	}
}