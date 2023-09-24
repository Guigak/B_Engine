#include "Object.h"
#include "Shader.h"

CObject::CObject() {
	DirectX::XMStoreFloat4x4(&m_xmf4x4_World, DirectX::XMMatrixIdentity());
}

CObject::~CObject() {
	if (m_pMesh) {
		m_pMesh->Release();
	}
	if (m_pShader) {
		m_pShader->Release_Shader_Variables();
		m_pShader->Release();
	}
}

void CObject::Release_Upload_Buffers() {
	if (m_pMesh) {
		m_pMesh->Release_Upload_Buffers();
	}
}

void CObject::Set_Mesh(CMesh* pMesh) {
	if (m_pMesh) {
		m_pMesh->Release();
	}

	m_pMesh = pMesh;

	if (m_pMesh) {
		m_pMesh->Add_Ref();
	}
}

void CObject::Set_Shader(CShader* pShader) {	// unused
	if (m_pShader) {
		m_pShader->Release();
	}

	m_pShader = pShader;

	if (m_pShader) {
		m_pShader->Add_Ref();
	}
}

void CObject::Anim(float fElapsed_Time) {
}

void CObject::Prepare_Render() {
}

void CObject::Render(ID3D12GraphicsCommandList* pd3d_Command_List) {
	Prepare_Render();

	if (m_pShader) {
		m_pShader->Render(pd3d_Command_List);
	}

	if (m_pMesh) {
		m_pMesh->Render(pd3d_Command_List);
	}
}
