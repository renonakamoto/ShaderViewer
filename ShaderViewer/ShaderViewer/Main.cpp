#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#include "Src/App/Config.h"

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
	ImGuiライブラリの初期化関数
*/
bool InitGui();

/*
	エントリーポイント
*/
int APIENTRY WinMain(
	_In_	  HINSTANCE hInstance_,
	_In_opt_  HINSTANCE hPrevInstance_,
	_In_	  LPSTR     lpCmpLine_,
	_In_	  INT       nCmdShow_)
{
#ifdef _DEBUG
	// メモリリークチェック
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Configの読み込み
	ConfigParameter::Load();

	//　Engineの初期化
	if (Engine::GetInstance()->Init(1280, 720, "ShaderViewer", hInstance_) == false)
	{
		return -1;
	}
	
	// ImGuiの初期化
	if (InitGui() == false)
	{
		return -2;
	}

	// アプリの初期化
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

	// ImGuiライブラリの解放
	ImGui::DestroyContext();
	// Enigineの解放
	Engine::GetInstance()->Release();

	return 0;
}

/*
	ImGuiライブラリの初期化
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