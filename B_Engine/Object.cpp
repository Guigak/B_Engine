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

void CObject::Set_Shader(CShader* pShader) {
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

void CObject::Render(ID3D12GraphicsCommandList* pd3d_Command_List, CCamera* pCamera) {
	Prepare_Render();

	if (m_pShader) {
		m_pShader->Udt_Shader_Variable(pd3d_Command_List, &m_xmf4x4_World);
		m_pShader->Render(pd3d_Command_List, pCamera);
	}

	if (m_pMesh) {
		m_pMesh->Render(pd3d_Command_List);
	}
}

void CObject::Rotate(DirectX::XMFLOAT3* pxmf3_Axis, float fAngle) {
	DirectX::XMMATRIX xmmtx_Rotate = DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(pxmf3_Axis), DirectX::XMConvertToRadians(fAngle));
	m_xmf4x4_World = Matrix4x4::Multiply(xmmtx_Rotate, m_xmf4x4_World);
}

//
CRotating_Object::CRotating_Object() {
	m_xmf3_Rotation_Axis = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_fRotation_Speed = 180.0f;
}

CRotating_Object::~CRotating_Object() {
}

void CRotating_Object::Anim(float fElapsed_Time) {
	CObject::Rotate(&m_xmf3_Rotation_Axis, m_fRotation_Speed * fElapsed_Time);
}
