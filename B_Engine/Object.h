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