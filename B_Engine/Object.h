#pragma once

#include "stdafx.h"
#include "Mesh.h"
#include "Camera.h"

class CShader;

class CObject {
private :
	int m_nReferences = 0;

protected :
	DirectX::XMFLOAT4X4 m_xmf4x4_World;
	CMesh* m_pMesh = NULL;

	CShader* m_pShader = NULL;

public :
	CObject();
	virtual ~CObject();

	//
	void Add_Ref() {
		++m_nReferences;
	}
	void Release() {
		if (--m_nReferences <= 0) {
			delete this;
		}
	}

	//
	void Release_Upload_Buffers();

	virtual void Set_Mesh(CMesh* pMesh);
	virtual void Set_Shader(CShader* pShader);

	virtual void Anim(float fElapsed_Time);

	virtual void Prepare_Render();
	virtual void Render(ID3D12GraphicsCommandList* pd3d_Command_List, CCamera* pCamera);

	void Rotate(DirectX::XMFLOAT3* pxmf3_Axis, float fAngle);

	//
	virtual void Crt_Shader_Variables(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List);
	virtual void Udt_Shader_Variables(ID3D12GraphicsCommandList* pd3d_Command_List);
	virtual void Release_Shader_Variables();

	DirectX::XMFLOAT3 Get_Position();
	DirectX::XMFLOAT3 Get_Look();
	DirectX::XMFLOAT3 Get_Up();
	DirectX::XMFLOAT3 Get_Right();

	void Set_Position(float x, float y, float z);
	void Set_Position(DirectX::XMFLOAT3 xmf3_Position);

	void Move_right(float fDistance = 1.0f);
	void Move_Up(float fDistance = 1.0f);
	void Move_Forward(float fDistance = 1.0f);

	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);
};

class CRotating_Object : public CObject {
private :
	DirectX::XMFLOAT3 m_xmf3_Rotation_Axis;
	float m_fRotation_Speed;

public :
	CRotating_Object();
	virtual ~CRotating_Object();

	void Set_Rotation_Axis(DirectX::XMFLOAT3 xmf3_Rotation_Axis) {
		m_xmf3_Rotation_Axis = xmf3_Rotation_Axis;
	}
	void Set_Rotation_Speed(float fRotation_Speed) {
		m_fRotation_Speed = fRotation_Speed;
	}

	virtual void Anim(float fElapsed_Time);
};