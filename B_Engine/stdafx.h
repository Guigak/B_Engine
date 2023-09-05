﻿// header.h: 표준 시스템 포함 파일
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

// Timer 관련
#include <Mmsystem.h>

#pragma comment(lib, "winmm.lib");

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
#pragma comment(lib, "d3dcompiler.lib");
#pragma comment(lib, "d3d12.lib");
#pragma comment(lib, "dxgi.lib");

#pragma comment(lib, "dxguid.lib");

// client rect size
#define FRAME_BUFFER_WIDTH	800
#define FRAME_BUFFER_HEIGHT	600