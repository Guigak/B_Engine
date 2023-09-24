#pragma once

#include "stdafx.h"
#include "Mesh.h"

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
	virtual void Set_Shader(CShader* pShader); // unused

	virtual void Anim(float fElapsed_Time);

	virtual void Prepare_Render();
	virtual void Render(ID3D12GraphicsCommandList* pd3d_Command_List);
};

