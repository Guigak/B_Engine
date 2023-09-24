#include "Mesh.h"

CMesh::CMesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List) {
}

CMesh::~CMesh() {
	if (m_pd3d_Vertex_Buffer) {
		m_pd3d_Vertex_Buffer->Release();
	}
	if (m_pd3d_Vertex_Upload_Buffer) {
		m_pd3d_Vertex_Upload_Buffer->Release();
	}
}

void CMesh::Release_Upload_Buffers() {
	if (m_pd3d_Vertex_Upload_Buffer) {
		m_pd3d_Vertex_Upload_Buffer->Release();
	}

	m_pd3d_Vertex_Upload_Buffer = NULL;
}

void CMesh::Render(ID3D12GraphicsCommandList* pd3d_Command_List) {
	pd3d_Command_List->IASetPrimitiveTopology(m_d3d_Primitive_Topology);
	pd3d_Command_List->IASetVertexBuffers(m_nSlot, 1, &m_d3d_Vertex_Buffer_View);
	pd3d_Command_List->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
}

CTriangle_Mesh::CTriangle_Mesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List) {
	m_nVertices = 3;
	m_nStride = sizeof(CDiffused_Vertex);
	m_d3d_Primitive_Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	CDiffused_Vertex pVertices[3];
	pVertices[0] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	pVertices[1] = CDiffused_Vertex(DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	pVertices[2] = CDiffused_Vertex(DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));

	m_pd3d_Vertex_Buffer = Crt_Buffer_Resource(pd3d_Device, pd3d_Command_List, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, & m_pd3d_Vertex_Upload_Buffer);

	m_d3d_Vertex_Buffer_View.BufferLocation = m_pd3d_Vertex_Buffer->GetGPUVirtualAddress();
	m_d3d_Vertex_Buffer_View.StrideInBytes = m_nStride;
	m_d3d_Vertex_Buffer_View.SizeInBytes = m_nStride * m_nVertices;
}