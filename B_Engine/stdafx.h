// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// io
#include <iostream>

// Timer 관련
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib")

// Direct3D 관련 headers
#include <string>
#include <wrl.h>
#include <shellapi.h>

#include <d3d12.h>
#include <dxgi1_4.h>

#include <D3Dcompiler.h>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>
#include <DirectXCollision.h>

#include <DXGIDebug.h>

//using namespace DirectX;
//using namespace DirectX::PackedVector;

using Microsoft::WRL::ComPtr;

// import library 추가
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#pragma comment(lib, "dxguid.lib")

// client rect size
#define FRAME_BUFFER_WIDTH	800
#define FRAME_BUFFER_HEIGHT	600

// fullscreen default
//#define _WITH_SWAPCHAIN_FULLSCREEN_STATE

// Create buffer resource
extern ID3D12Resource* Crt_Buffer_Resource(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List, void* pData, UINT nBytes, D3D12_HEAP_TYPE d3d_HeapType = D3D12_HEAP_TYPE_UPLOAD,
	D3D12_RESOURCE_STATES d3d_Resource_States = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, ID3D12Resource** ppd3d_UploadBuffer = NULL);

// about calculate
namespace Vector3 {

	inline DirectX::XMFLOAT3 XMVector_2_Float3(DirectX::XMVECTOR& xmvVector) {	// vector -> float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, xmvVector);

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Multiply(DirectX::XMFLOAT3& xmf3Vector, float fScalar, bool bNormalize = true) {	// float3 * float
		DirectX::XMFLOAT3 xmf3Result;

		if (bNormalize) {
			DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVectorScale(DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&xmf3Vector)), fScalar));
		}
		else {
			DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVectorScale(DirectX::XMLoadFloat3(&xmf3Vector), fScalar));
		}

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Add(const DirectX::XMFLOAT3& xmf3Vector1, const DirectX::XMFLOAT3& xmf3Vector2) {	// float3 + float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2)));

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Add(DirectX::XMFLOAT3& xmf3Vector1, DirectX::XMFLOAT3& xmf3Vector2, float fScalar) {	// float3 + float3 * float
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMVectorScale(DirectX::XMLoadFloat3(&xmf3Vector2), fScalar)));

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Subtract(DirectX::XMFLOAT3& xmf3Vector1, DirectX::XMFLOAT3& xmf3Vector2) {	// float3 - float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2)));

		return xmf3Result;
	}

	inline float Dot_Product(DirectX::XMFLOAT3& xmf3Vector1, DirectX::XMFLOAT3& xmf3Vector2) {	// float3 dot float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3Dot(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2)));

		return xmf3Result.x;
	}

	inline DirectX::XMFLOAT3 Cross_Product(DirectX::XMFLOAT3& xmf3Vector1, DirectX::XMFLOAT3& xmf3Vector2, bool bNormalize = true) {	// float3 cross float3
		DirectX::XMFLOAT3 xmf3Result;

		if (bNormalize) {
			DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2))));
		}
		else {
			DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2)));
		}

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Normalize(DirectX::XMFLOAT3& xmf3Vector) {	// normalize float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&xmf3Vector)));

		return xmf3Result;
	}

	inline float Length(DirectX::XMFLOAT3& xmf3Vector) {	// length of float3
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3Length(DirectX::XMLoadFloat3(&xmf3Vector)));

		return xmf3Result.x;
	}

	inline float Angle(DirectX::XMVECTOR& xmvVector1, DirectX::XMVECTOR& xmvVector2) {	// angle btw vector & vector
		DirectX::XMVECTOR xmvAngle = DirectX::XMVector3AngleBetweenNormals(xmvVector1, xmvVector2);
		return DirectX::XMConvertToDegrees(acosf(DirectX::XMVectorGetX(xmvAngle)));
	}

	inline float Angle(DirectX::XMFLOAT3& xmf3Vector1, DirectX::XMFLOAT3& xmf3Vector2) {	// angle btw float3 & float3
		return Angle(DirectX::XMLoadFloat3(&xmf3Vector1), DirectX::XMLoadFloat3(&xmf3Vector2));
	}

	inline DirectX::XMFLOAT3 Transform_Normal(DirectX::XMFLOAT3& xmf3Vector, DirectX::XMMATRIX& xmmtxTransform) {
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3TransformNormal(DirectX::XMLoadFloat3(&xmf3Vector), xmmtxTransform));

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Transform_Coord(DirectX::XMFLOAT3& xmf3Vector, DirectX::XMMATRIX& xmmtxTransform) {
		DirectX::XMFLOAT3 xmf3Result;
		DirectX::XMStoreFloat3(&xmf3Result, DirectX::XMVector3TransformCoord(DirectX::XMLoadFloat3(&xmf3Vector), xmmtxTransform));

		return xmf3Result;
	}

	inline DirectX::XMFLOAT3 Transform_Coord(DirectX::XMFLOAT3& xmf3Vector, DirectX::XMFLOAT4X4& xmmtx4x4Matrix) {
		return Transform_Coord(xmf3Vector, DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix));
	}
}

namespace Vector4 {
	inline DirectX::XMFLOAT4 Add(DirectX::XMFLOAT4& xmf4Vector1, DirectX::XMFLOAT4& xmf4Vector2) {	// float4 + float4
		DirectX::XMFLOAT4 xmf4Result;
		DirectX::XMStoreFloat4(&xmf4Result, DirectX::XMVectorAdd(DirectX::XMLoadFloat4(&xmf4Vector1), DirectX::XMLoadFloat4(&xmf4Vector2)));

		return xmf4Result;
	}

	inline DirectX::XMFLOAT4 Multiply(DirectX::XMFLOAT4& xmf4Vector1, DirectX::XMFLOAT4& xmf4Vector2) {	// float4 * float4
		DirectX::XMFLOAT4 xmf4Result;
		DirectX::XMStoreFloat4(&xmf4Result, DirectX::XMVectorMultiply(DirectX::XMLoadFloat4(&xmf4Vector1), DirectX::XMLoadFloat4(&xmf4Vector2)));

		return xmf4Result;
	}

	inline DirectX::XMFLOAT4 Multiply(DirectX::XMFLOAT4& xmf4Vector, float fScalar) {	// float4 * float
		DirectX::XMFLOAT4 xmf4Result;
		DirectX::XMStoreFloat4(&xmf4Result, DirectX::XMVectorScale(DirectX::XMLoadFloat4(&xmf4Vector), fScalar));
		
		return xmf4Result;
	}
}

namespace Matrix4x4 {
	inline DirectX::XMFLOAT4X4 Identity() {
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixIdentity());

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 Multiply(DirectX::XMFLOAT4X4& xmmtx4x4Matrix1, DirectX::XMFLOAT4X4& xmmtx4x4Matrix2) {
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix1), DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix2)));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 Multiply(DirectX::XMFLOAT4X4& xmmtx4x4Matrix1, DirectX::XMMATRIX& xmmtx4x4Matrix2) {
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixMultiply(DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix1), xmmtx4x4Matrix2));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 Multiply(DirectX::XMMATRIX& xmmtx4x4Matrix1, DirectX::XMFLOAT4X4& xmmtx4x4Matrix2) {
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixMultiply(xmmtx4x4Matrix1, DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix2)));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 Inverse(DirectX::XMFLOAT4X4& xmmtx4x4Matrix) {	// Inverse
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixInverse(NULL, DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix)));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 Transpose(DirectX::XMFLOAT4X4& xmmtx4x4Matrix) {	// Transpose
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixTranspose(DirectX::XMLoadFloat4x4(&xmmtx4x4Matrix)));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 PerspectiveFov_LH(float FovAngle_Y, float Aspect_Ratio, float Near_Z, float Far_Z) {	// Projection Matrix
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixPerspectiveFovLH(FovAngle_Y, Aspect_Ratio, Near_Z, Far_Z));

		return xmmtx4x4Result;
	}

	inline DirectX::XMFLOAT4X4 LookAt_LH(DirectX::XMFLOAT3& xmf3Eye_Position, DirectX::XMFLOAT3& xmf3LookAt_Position, DirectX::XMFLOAT3& xmf3Up_Direction) {	// View Matrix
		DirectX::XMFLOAT4X4 xmmtx4x4Result;
		DirectX::XMStoreFloat4x4(&xmmtx4x4Result, DirectX::XMMatrixLookAtLH(DirectX::XMLoadFloat3(&xmf3Eye_Position), DirectX::XMLoadFloat3(&xmf3LookAt_Position), DirectX::XMLoadFloat3(&xmf3Up_Direction)));

		return xmmtx4x4Result;
	}
}
