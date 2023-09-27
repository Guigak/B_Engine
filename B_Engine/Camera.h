#pragma once

#include "stdafx.h"

#define ASPECT_RATIO (float(FRAME_BUFFER_WIDTH) / float(FRAME_BUFFER_HEIGHT))

struct VS_CB_CAMERA_INFO {
	DirectX::XMFLOAT4X4 m_xmf4x4_View;
	DirectX::XMFLOAT4X4 m_xmf4x4_Projection;
};

class CCamera {
protected :
	DirectX::XMFLOAT4X4 m_xmf4x4_View;
	DirectX::XMFLOAT4X4 m_xmf4x4_Projection;

	D3D12_VIEWPORT m_d3d_Viewport;
	D3D12_RECT m_d3d_ScissorRect;

public :
	CCamera();
	virtual ~CCamera();

	virtual void Crt_Shader_Variables(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List);
	virtual void Release_Shader_Variables();
	virtual void Udt_Shader_Variables(ID3D12GraphicsCommandList* pd3d_Command_List);

	void Generate_View_Matrix(DirectX::XMFLOAT3 xmf3_Position, DirectX::XMFLOAT3 xmf3_LookAt, DirectX::XMFLOAT3 xmf3_Up);
	void Gernerate_projection_Matrix(float fFovAngle, float fAspect_Ratio, float fNear_Plane_Distance, float fFar_Plane_Distance);

	void Set_Viewport(int x_Top_Left, int y_Top_Left, int nWidth, int nHeight, float fMin_Z = 0.0f, float fMax_Z = 1.0f);
	void Set_ScissorRect(LONG x_Left, LONG y_top, LONG x_Right, LONG y_Bottom);

	virtual void Set_Viewports_N_ScissorRects(ID3D12GraphicsCommandList* pd3d_Command_List);
};

