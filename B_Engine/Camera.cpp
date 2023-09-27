#include "Camera.h"

CCamera::CCamera() {
	m_xmf4x4_View = Matrix4x4::Identity();
	m_xmf4x4_Projection = Matrix4x4::Identity();
	m_d3d_Viewport = { 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT, 0.0f, 1.0f };
	m_d3d_ScissorRect = { 0, 0, FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT };
}

CCamera::~CCamera() {
}

void CCamera::Crt_Shader_Variables(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List) {
}

void CCamera::Release_Shader_Variables() {
}

void CCamera::Udt_Shader_Variables(ID3D12GraphicsCommandList* pd3d_Command_List) {
	DirectX::XMFLOAT4X4 xmf4x4_View;
	DirectX::XMStoreFloat4x4(&xmf4x4_View, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_xmf4x4_View)));
	pd3d_Command_List->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4_View, 0);

	DirectX::XMFLOAT4X4 xmf4x4_Projection;
	DirectX::XMStoreFloat4x4(&xmf4x4_Projection, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&m_xmf4x4_Projection)));
	pd3d_Command_List->SetGraphicsRoot32BitConstants(1, 16, &xmf4x4_Projection, 16);
}

void CCamera::Generate_View_Matrix(DirectX::XMFLOAT3 xmf3_Position, DirectX::XMFLOAT3 xmf3_LookAt, DirectX::XMFLOAT3 xmf3_Up) {
	m_xmf4x4_View = Matrix4x4::LookAt_LH(xmf3_Position, xmf3_LookAt, xmf3_Up);
}

void CCamera::Gernerate_projection_Matrix(float fFovAngle, float fAspect_Ratio, float fNear_Plane_Distance, float fFar_Plane_Distance) {
	m_xmf4x4_Projection = Matrix4x4::PerspectiveFov_LH(DirectX::XMConvertToRadians(fFovAngle), fAspect_Ratio, fNear_Plane_Distance, fFar_Plane_Distance);
}

void CCamera::Set_Viewport(int x_Top_Left, int y_Top_Left, int nWidth, int nHeight, float fMin_Z, float fMax_Z) {
	m_d3d_Viewport.TopLeftX = float(x_Top_Left);
	m_d3d_Viewport.TopLeftY = float(y_Top_Left);
	m_d3d_Viewport.Width = float(nWidth);
	m_d3d_Viewport.Height = float(nHeight);
	m_d3d_Viewport.MinDepth = fMin_Z;
	m_d3d_Viewport.MaxDepth = fMax_Z;
}

void CCamera::Set_ScissorRect(LONG x_Left, LONG y_top, LONG x_Right, LONG y_Bottom) {
	m_d3d_ScissorRect.left = x_Left;
	m_d3d_ScissorRect.top = y_top;
	m_d3d_ScissorRect.right = x_Right;
	m_d3d_ScissorRect.bottom = y_Bottom;
}

void CCamera::Set_Viewports_N_ScissorRects(ID3D12GraphicsCommandList* pd3d_Command_List) {
	pd3d_Command_List->RSSetViewports(1, &m_d3d_Viewport);
	pd3d_Command_List->RSSetScissorRects(1, &m_d3d_ScissorRect);
}
