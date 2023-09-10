#pragma once

#include "Timer.h"

class CScene {
public :
	CScene();
	~CScene();

	bool Prcs_Msg_Mouse(HWND hWnd, UINT nMsg_ID, WPARAM wParam, LPARAM lParam);
	bool Prcs_Msg_Keyboard(HWND hWnd, UINT nMsg_ID, WPARAM wParam, LPARAM lParam);

	void Crt_Graphics_RootSignature(ID3D12Device* pd3d_Device);
	void Crt_Graphics_Pipeline_State(ID3D12Device* pd3d_Device);

	void Build_Objects(ID3D12Device* pd3d_Device);
	void Release_Objects();

	bool Prcs_Input();
	void Anim_Objects(float fElapsed_Time);

	void Prepare_Render(ID3D12GraphicsCommandList* pd3d_Command_List);
	void Render(ID3D12GraphicsCommandList* pd3d_Command_List);

	ID3D12RootSignature* m_pd3d_Graphics_RootSignature = NULL;
	ID3D12PipelineState* m_pd3d_Graphics_Pipeline_State = NULL;
};

