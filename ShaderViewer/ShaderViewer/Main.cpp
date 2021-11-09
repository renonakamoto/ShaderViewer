#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Src/Engine/Engine.h"
#include "Src/Engine/imGui/imgui.h"
#include "Src/Engine/imGui/imgui_impl_win32.h"
#include "Src/Engine/imGui/imgui_impl_dx11.h"

#include "Src/App/Lighting/Phong.h"
#include "Src/App/Lighting/BlinnPhong.h"

#include "Src/Engine/Shader/ShaderManager.h"
#include "Src/App/Lighting/LightingManager.h"

#include "Src/App/ViewModel/ViewModel.h"
#include "Src/App/Camera/Camera.h"

#include "Src/App/App.h"

#pragma comment(lib, "winmm.lib")

/*
	ImGui���C�u�����̏������֐�
*/
bool InitGui();

/*
	�G���g���[�|�C���g
*/
int APIENTRY WinMain(
	_In_	  HINSTANCE hInstance,
	_In_opt_  HINSTANCE hPrevInstance,
	_In_	  LPSTR     lpCmpLine,
	_In_	  INT       nCmdShow)
{
#ifdef _DEBUG
	// ���������[�N�`�F�b�N
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//�@Engine�̏�����
	if (Engine::GetInstance()->Init(1280, 720, "ShaderViewer", hInstance) == false)
	{
		return -1;
	}
	
	// ImGui�̏�����
	if (InitGui() == false)
	{
		return -2;
	}

	// �A�v���̏�����
	if (APP->Init() == false)
	{
		return -3;
	}

	while (true)
	{
		MSG msg{ 0 };

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			APP->Run();
		}
	}

	// ImGui���C�u�����̉��
	ImGui::DestroyContext();
	// Enigine�̉��
	Engine::GetInstance()->Release();

	return 0;
}

/*
	ImGui���C�u�����̏�����
*/
bool InitGui()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsLight();

	if (!ImGui_ImplWin32_Init(WINDOW->GetWindowHandle()))
	{
		ImGui::DestroyContext();
		Engine::GetInstance()->Release();
		return false;
	}
	if (!ImGui_ImplDX11_Init(GRAPHICS->GetDevice(), GRAPHICS->GetContext()))
	{
		ImGui::DestroyContext();
		Engine::GetInstance()->Release();
		return false;
	}

	return true;
}