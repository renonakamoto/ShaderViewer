#include "Engine.h"

bool Engine::Init(int windowWidth_, int windowHeight_, const char* titleName_, HINSTANCE hInstance_)
{
	// Windowの作成
	if (m_Window.Create(windowWidth_, windowHeight_, titleName_) == false)
	{
		return false;
	}

	// Graphicsの初期化
	if (m_Graphics.Init() == false)
	{
		return false;
	}

	// Soundの初期化
	if (m_Sound.Init(m_Window.GetWindowHandle()) == false)
	{
		return false;
	}

	// Textureの初期化
	if (m_Texture.Init(m_Graphics.GetDevice()) == false)
	{
		return false;
	}

	// Engineの初期化成功
	return true;
}

void Engine::Release()
{
	m_Graphics.Release();
	m_Sound.Release();
	m_Texture.AllRelease();
}