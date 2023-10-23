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

	//
	if (m_pd3d_Index_Buffer) {
		m_pd3d_Index_Buffer->Release();
	}
	if (m_pd3d_Index_Upload_Buffer) {
		m_pd3d_Index_Upload_Buffer->Release();
	}
}

void CMesh::Release_Upload_Buffers() {
	if (m_pd3d_Vertex_Upload_Buffer) {
		m_pd3d_Vertex_Upload_Buffer->Release();
	}
	m_pd3d_Vertex_Upload_Buffer = NULL;

	if (m_pd3d_Index_Upload_Buffer) {
		m_pd3d_Index_Upload_Buffer->Release();
	}
	m_pd3d_Index_Upload_Buffer = NULL;
}

void CMesh::Render(ID3D12GraphicsCommandList* pd3d_Command_List) {
	pd3d_Command_List->IASetPrimitiveTopology(m_d3d_Primitive_Topology);
	pd3d_Command_List->IASetVertexBuffers(m_nSlot, 1, &m_d3d_Vertex_Buffer_View);

	if (m_pd3d_Index_Buffer) {
		pd3d_Command_List->IASetIndexBuffer(&m_d3d_Index_Buffer_View);
		pd3d_Command_List->DrawIndexedInstanced(m_nIndices, 1, 0, 0, 0);
	}
	else {
		pd3d_Command_List->DrawInstanced(m_nVertices, 1, m_nOffset, 0);
	}
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

CCube_Mesh::CCube_Mesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List, float fWidth, float fHeight, float fDepth) {
	m_nVertices = 8;
	m_nStride = sizeof(CDiffused_Vertex);
	m_d3d_Primitive_Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth * 0.5f;
	float fy = fHeight * 0.5f;
	float fz = fDepth * 0.5f;

	CDiffused_Vertex pVertices[8];
	pVertices[0] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, +fy, -fz), RANDOM_COLOR);
	pVertices[1] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, +fy, -fz), RANDOM_COLOR);
	pVertices[2] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, +fy, +fz), RANDOM_COLOR);
	pVertices[3] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, +fy, +fz), RANDOM_COLOR);
	pVertices[4] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -fy, -fz), RANDOM_COLOR);
	pVertices[5] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -fy, -fz), RANDOM_COLOR);
	pVertices[6] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -fy, +fz), RANDOM_COLOR);
	pVertices[7] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -fy, +fz), RANDOM_COLOR);

	m_pd3d_Vertex_Buffer = Crt_Buffer_Resource(pd3d_Device, pd3d_Command_List, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3d_Vertex_Upload_Buffer);

	m_d3d_Vertex_Buffer_View.BufferLocation = m_pd3d_Vertex_Buffer->GetGPUVirtualAddress();
	m_d3d_Vertex_Buffer_View.StrideInBytes = m_nStride;
	m_d3d_Vertex_Buffer_View.SizeInBytes = m_nStride * m_nVertices;

	//
	m_nIndices = 36;
	UINT pnIndices[36];

	//front
	pnIndices[0] = 3;
	pnIndices[1] = 1;
	pnIndices[2] = 0;
	pnIndices[3] = 2;
	pnIndices[4] = 1;
	pnIndices[5] = 3;

	// top
	pnIndices[6] = 0;
	pnIndices[7] = 5;
	pnIndices[8] = 4;
	pnIndices[9] = 1;
	pnIndices[10] = 5;
	pnIndices[11] = 0;

	// back
	pnIndices[12] = 3;
	pnIndices[13] = 4;
	pnIndices[14] = 7;
	pnIndices[15] = 0;
	pnIndices[16] = 4;
	pnIndices[17] = 3;

	// bottom
	pnIndices[18] = 1;
	pnIndices[19] = 6;
	pnIndices[20] = 5;
	pnIndices[21] = 2;
	pnIndices[22] = 6;
	pnIndices[23] = 1;

	// left
	pnIndices[24] = 2;
	pnIndices[25] = 7;
	pnIndices[26] = 6;
	pnIndices[27] = 3;
	pnIndices[28] = 7;
	pnIndices[29] = 2;

	// right
	pnIndices[30] = 6;
	pnIndices[31] = 4;
	pnIndices[32] = 5;
	pnIndices[33] = 7;
	pnIndices[34] = 4;
	pnIndices[35] = 6;

	m_pd3d_Index_Buffer = Crt_Buffer_Resource(pd3d_Device, pd3d_Command_List, pnIndices, sizeof(UINT) * m_nIndices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_INDEX_BUFFER, &m_pd3d_Index_Upload_Buffer);

	m_d3d_Index_Buffer_View.BufferLocation = m_pd3d_Index_Buffer->GetGPUVirtualAddress();
	m_d3d_Index_Buffer_View.Format = DXGI_FORMAT_R32_UINT;
	m_d3d_Index_Buffer_View.SizeInBytes = sizeof(UINT) * m_nIndices;
}

CCube_Mesh::~CCube_Mesh()
{
}


//
CAirPlane_Mesh::CAirPlane_Mesh(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List, float fWidth, float fHeight, float fDepth, DirectX::XMFLOAT4 xmf4_Color) : CMesh(pd3d_Device, pd3d_Command_List){
	m_nVertices = 24 * 3;
	m_nStride = sizeof(CDiffused_Vertex);
	m_nOffset = 0;
	m_nSlot = 0;
	m_d3d_Primitive_Topology = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	float fx = fWidth * 0.5f;
	float fy = fHeight * 0.5f;
	float fz = fDepth * 0.5f;

	CDiffused_Vertex pVertices[24 * 3];

	float x1 = fx * 0.2f;
	float y1 = fy * 0.2f;
	float x2 = fx * 0.1f;
	float y3 = fy * 0.3f;
	float y2 = ((y1 - (fy - y3)) / x1) * x2 + (fy - y3);

	int i = 0;

	// top
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), -fz),	Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	// bottom
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	// right
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	// back right
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(+x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	// left
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, +(fy + y3), +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x2, +y2, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	// back left
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(0.0f, 0.0f, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-x1, -y1, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, +fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));
	pVertices[i++] = CDiffused_Vertex(DirectX::XMFLOAT3(-fx, -y3, -fz), Vector4::Add(xmf4_Color, RANDOM_COLOR));

	m_pd3d_Vertex_Buffer = Crt_Buffer_Resource(pd3d_Device, pd3d_Command_List, pVertices, m_nStride * m_nVertices, D3D12_HEAP_TYPE_DEFAULT, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, &m_pd3d_Vertex_Upload_Buffer);

	m_d3d_Vertex_Buffer_View.BufferLocation = m_pd3d_Vertex_Buffer->GetGPUVirtualAddress();
	m_d3d_Vertex_Buffer_View.StrideInBytes = m_nStride;
	m_d3d_Vertex_Buffer_View.SizeInBytes = m_nStride * m_nVertices;
}

CAirPlane_Mesh::~CAirPlane_Mesh() {
}
