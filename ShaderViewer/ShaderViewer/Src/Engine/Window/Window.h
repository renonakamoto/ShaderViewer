#ifndef WINDOW_H_
#define WINDOW_H_

#include <Windows.h>

/**
* @brief ウィンドウの管理を行うクラス
*/
class Window
{
public:
	//! ウィンドウのクラス名
	static const char* ClassName;
	
public:
	static LRESULT CALLBACK WindowProc(HWND windowHandle_, UINT messageId_, WPARAM wparam_, LPARAM lparam_);
	
public:
	/**
	* @brief コンストラクタ
	*/
	Window():
		m_WindowHandle(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~Window(){}

	/**
	* @fn bool Create()
	* @brief ウィンドウ作成する関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Create(int windowWidth_, int windowHeight, const char* titleName_);

public:
	/**
	* @fn void GetWindowHandle()
	* @brief ウィンドウハンドルを返す関数
	* @return HWND ウィンドウハンドルを返す
	*/
	HWND GetWindowHandle() { return m_WindowHandle; }

	/**
	* @fn void GetClientWidth()
	* @brief ウィンドウの横幅を返す関数
	* @return int クライアントの横幅を返す
	*/
	int GetClientWidth()  { return m_Width;  }

	/**
	* @fn void GetClientHeight()
	* @brief ウィンドウの縦幅を返す関数
	* @return int クライアントの縦幅を返す
	*/
	int GetClientHeight() { return m_Height; }

private:
	/**
	* @fn bool EntryWindowClass()
	* @brief ウィンドウクラスを登録する
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool EntryWindowClass();

	/**
	* @fn void SetCenterWindow(HWND windowHandle_)
	* @brief ウィンドウを真ん中にセットする関数
	* @param[in] windowHandle_ ウィンドウハンドル
	*/
	void SetCenterWindow(HWND windowHandle_);

private:
	static int m_Width;		//! ウィンドウの横幅
	static int m_Height;	//! ウィンドウの縦幅
	HWND m_WindowHandle;	//! ウィンドウハンドル
};

#endif