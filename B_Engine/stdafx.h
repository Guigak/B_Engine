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

extern ID3D12Resource* Crt_Buffer_Resource(ID3D12Device* pd3d_Device, ID3D12GraphicsCommandList* pd3d_Command_List, void* pData, UINT nBytes, D3D12_HEAP_TYPE d3d_HeapType = D3D12_HEAP_TYPE_UPLOAD,
	D3D12_RESOURCE_STATES d3d_Resource_States = D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER, ID3D12Resource** ppd3d_UploadBuffer = NULL);
