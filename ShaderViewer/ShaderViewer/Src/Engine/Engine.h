#ifndef ENGINE_H_
#define ENGINE_H_

#include "Window/Window.h"
#include "Graphics/DirectGraphics.h"
#include "Input/InputManager.h"
#include "Sound/SoundManager.h"
#include "Texture/TextureManager.h"

/**
* @brief エンジンの管理クラス
*/
class Engine
{
public:
	/**
	* @fn static Engine* GetInstance()
	* @brief インスタンスを返す関数
	* @return Engine* インスタンスのポインタ
	*/
	static Engine* GetInstance()
	{
		static Engine instance;
		return &instance;
	}

	/**
	* @fn bool Init()
	* @brief エンジンの初期化関数
	* @param[in] windowWidth_  ウィンドウの横幅
	* @param[in] windowHeight_ ウィンドウの縦幅
	* @param[in] titleName_	   ウィンドウ名
	* @param[in] hInstance_	   インスタンスハンドル
	* @return bool 成功したかどうかを真偽で返す
	* @details プログラム開始時に一度だけ呼び出す
	*/
	bool Init(int windowWidth_, int windowHeight_, const char* titleName_, HINSTANCE hInstance_);

	/**
	* @fn void Release()
	* @brief エンジンの解放関数
	* @details プログラムの終了時に一度だけ呼び出す
	*/
	void Release();

public:
	/**
	* @fn Window* GetWindow()
	* @brief Windowの取得関数
	* @return Window* Windowのポインタ
	*/
	Window* GetWindow() { return &m_Window; }

	/**
	* @fn DirectGraphics* GetGraphics()
	* @brief Graphicsの取得関数
	* @return DirectGraphics* Graphicsのポインタ
	*/
	DirectGraphics* GetGraphics() { return &m_Graphics; }

	/**
	* @fn InputManager* GetInput()
	* @brief InputManagerの取得関数
	* @return InputManager* InputManagerのポインタ
	*/
	InputManager* GetInput() { return &m_Input; }

	/**
	* @fn SoundManager* GetSound()
	* @brief SoundManagerの取得関数
	* @return SoundManager* SoundManagerのポインタ
	*/
	SoundManager* GetSound() { return &m_Sound; }

	/**
	* @fn TextureManager* GetTexture()
	* @brief TextureManagerの取得関数
	* @return TextureManager* TextureManagerのポインタ
	*/
	TextureManager* GetTexture() { return &m_Texture; }

private:
	/**
	* @brief コンストラクタ
	*/
	Engine()
	{}

	/**
	* @brief デストラクタ
	*/
	~Engine()
	{
		Release();
	}

private:
	Window         m_Window;	//! ウィンドウクラス
	DirectGraphics m_Graphics;	//! グラフィッククラス
	InputManager   m_Input;		//! 入力管理クラス
	SoundManager   m_Sound;		//! サウンド管理クラス
	TextureManager m_Texture;	//! テクスチャ管理クラス
};

// 簡易アクセス用
#define WINDOW			(Engine::GetInstance()->GetWindow())
#define GRAPHICS		(Engine::GetInstance()->GetGraphics())
#define INPUT_MANAGER	(Engine::GetInstance()->GetInput())
#define SOUND			(Engine::GetInstance()->GetSound())
#define TEX_MANAGER		(Engine::GetInstance()->GetTexture())

#endif