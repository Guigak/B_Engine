#pragma once

#include "stdafx.h"

class CVertex {
protected :
	DirectX::XMFLOAT3 m_xmf3_Position;

public :
	CVertex() {
		m_xmf3_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	CVertex(DirectX::XMFLOAT3 xmf3_Position) {
		m_xmf3_Position = xmf3_Position;
	}
	~CVertex() {};
};

class CDiffused_Vertex : public CVertex {
protected :
	DirectX::XMFLOAT4 m_xmf4_Diffuse;

public :
	CDiffused_Vertex() {
		m_xmf3_Position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
		m_xmf4_Diffuse = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
	}
	CDiffused_Vertex(float x, float y, float z, DirectX::XMFLOAT4 xmf4_Diffuse) {
		m_xmf3_Position = DirectX::XMFLOAT3(x, y, z);
		m_xmf4_Diffuse = xmf4_Diffuse;
	}
	CDiffused_Vertex(DirectX::XMFLOAT3 xmf3_Position, DirectX::XMFLOAT4 xmf4_Diffuse) {
		m_xmf3_Position = xmf3_Position;
		m_xmf4_Diffuse = xmf4_Diffuse;
	}
	~CDiffused_Vertex() {};
};

class CMesh {
private :
	int m_nReferences = 0;

protected :
	ID3D12Resource* m_pd3d_Vertex_Buffer = NULL;
	ID3D12Resource* m_pd3d_Vertex_Upload_Buffer = NULL;

	D3D12_VERTEX_BUFFER_VIEW m_d3d_Vertex_Buffer_View;

	D3D12_PRIMITIVE_TOPOLOGY m_d3d_Primitive_Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	UINT m_nSlot = 0;
	UINT m_nVertices = 0;
	UINT m_nStride = 0;
	UINT m_nOffset = 0;

public :
	CMesh() = default;
	CMesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List);
	virtual ~CMesh();

	void Add_Ref() {
		++m_nReferences;
	}
	void Release() {
		if (--m_nReferences <= 0) {
			delete this;
		}
	}

	void Release_Upload_Buffers();

public :
	virtual void Render(ID3D12GraphicsCommandList* pd3d_Command_List);
};

class CTriangle_Mesh : public CMesh {
public :
	CTriangle_Mesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List);
	virtual ~CTriangle_Mesh() {};
};