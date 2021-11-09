/*

*/


#ifndef INPUT_M
#define INPUT_M

#include <dinput.h>
#include <XInput.h>
#include <vector>
#include <Windows.h>

#define MAX_CONTROLLERS 4	//!< XInputの取得可能な最大コントローラー数

enum class InputState
{
	Not_Push,
	Release,
	PushDown,
	Push,
};

enum class MouseButton
{
	Left,
	Right,
	Center,
	Max_Mouse_Btn
};

enum class KeyInfo
{
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_Up,
	Key_Down,
	Key_Right,
	Key_Left,
	Key_Return,
	Key_ESC,
	Key_Space,
	Key_1,
	Key_2,
	Key_3,
	Key_4,
	Key_5,
	Key_6,
	Key_7,
	Key_8,
	Key_9,
	Key_0,

	Max_Key_Info
};

enum class XInput_Button
{
	DPad_Up,
	DPad_Down,
	DPad_Left,
	DPad_Right,
	Start,
	Back,
	Left_Thumb,
	Right_Thumb,
	Left_Shoulder,
	Right_Shoulder,
	A,
	B,
	X,
	Y,
	Left_Trigger,
	Right_Trigger,
	L_Up,
	L_Down,
	L_Left,
	L_Right,
	R_Up,
	R_Down,
	R_Left,
	R_Right,
	MAX_INFO,
};

enum class InputInfo
{
	Key_A,
	Key_B,
	Key_C,
	Key_D,
	Key_E,
	Key_F,
	Key_G,
	Key_H,
	Key_I,
	Key_J,
	Key_K,
	Key_L,
	Key_M,
	Key_N,
	Key_O,
	Key_P,
	Key_Q,
	Key_R,
	Key_S,
	Key_T,
	Key_U,
	Key_V,
	Key_W,
	Key_X,
	Key_Y,
	Key_Z,
	Key_Up,
	Key_Down,
	Key_Right,
	Key_Left,
	Key_Return,
	Key_ESC,
	Key_Space,
	Mouse_Left,
	Mouse_Right,
	Mouse_Wheel,
	DPad_Up,
	DPad_Down,
	DPad_Left,
	DPad_Right,
	Start,
	Back,
	Left_Thumb,
	Right_Thumb,
	Left_Shoulder,
	Right_Shoulder,
	A,
	B,
	X,
	Y,
	Left_Trigger,
	Right_Trigger,
	L_Up,
	L_Down,
	L_Left,
	L_Right,
	R_Up,
	R_Down,
	R_Left,
	R_Right,
	Max_ID,
};

enum class InputMode
{
	MODE_GAME,
	MODE_UI,
};

class InputManager
{
public:
	/**
	* @biref コンストラクタ
	*/
	InputManager();

	/**
	* @biref デストラクタ
	*/
	~InputManager() { }

	/**
	* @brief Input機能の初期化関数
	* デバイスの入力取得に必要な初期化を行います
	* @return 初期化結果、成功の場合はtrue
	* @param[in] hInstance_	インスタンスハンドル
	* @param[in] hWindow_	ウィンドウハンドル
	*/
	bool Init(HINSTANCE hInstance_, HWND hWindow_);

	/**
	* @brief Input機能の終了関数
	* Input機能を終了させます
	*/
	void Release();

	/**
	* @biref 入力情報の更新
	* マウス、キーボード、ゲームパッドの入力情報の更新を行います
	*/
	void Update();


//!< 以下マウス関連の関数
	/***
	* @biref マウスが押されているかの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouse(MouseButton button_)const;

	/***
	* @biref マウスが押された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseDown(MouseButton button_)const;

	/***
	* @biref マウスが離された瞬間かの情報取得関数
	* @param[in] button_ マウスのボタンの種類
	*/
	bool GetMouseUp(MouseButton button_)const;

	/***
	* @biref マウス座標の取得関数
	*/
	POINT GetMousePos()const;

//!< 以下キーボード関連の関数
	/***
	* @biref キーが押されているかの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKey(KeyInfo key_)const;

	/***
	* @biref キーが押された瞬間かの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKeyDown(KeyInfo key_)const;

	/***
	* @biref キーが離された瞬間かの情報取得関数
	* @param[in] button_ キーの種類
	*/
	bool GetKeyUp(KeyInfo key_)const;

//!< 以下ゲームパッド関連の関数
	/**
	* @brief ボタンが押されているかの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButton(XInput_Button btn_)const;

	/**
	* @brief ボタンが押されてた瞬間かの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButtonDown(XInput_Button btn_)const;

	/**
	* @brief ボタンが離された瞬間かの情報取得関数
	* @param[in] num_ コントローラーの番号
	* @param[in] btn_ ボタンの種類
	*/
	bool GetButtonUp(XInput_Button btn_)const;

//!< 以下仮想コントローラー用
	int GetInputState(InputInfo id_)const;

	void SetMousePos(int x, int y);

	void SetInputMode(InputMode mode);
	InputMode GetInputMode() { return m_InputMode; };

	float GetMouseMovementX() { return m_MovementX * m_MouseSensitivity; }
	float GetMouseMovementY() { return m_MovementY * m_MouseSensitivity; }

	void SetMousemSensitivity(float sensitivity) { m_MouseSensitivity = sensitivity; }
	float GetMousemSensitivity() { return m_MouseSensitivity; }

private:
	/**
	* @brief キーボード用のデバイスの生成
	* キーボード用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateKeyDevice(HWND hWindow_);

	/**
	* @brief キーボードの入力情報更新関数
	*/
	void UpdateKeyState();

	/**
	* @brief マウス用のデバイスの生成
	* マウス用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	*/
	bool CreateMouseDevice(HWND hWindow_);

	/**
	* @brief マウスの入力情報更新関数
	*/
	void UpdateMouseState();

	/**
	* @brief ゲームパッド用のデバイス生成
	* ゲームパッド用のDirectInputDeviceを生成、初期化します
	* @return 生成結果、成功の場合はtrue
	* @param[in] hWindow_ ウィンドウハンドル
	*/
	bool CreateGamePadDevice(HWND hWindow_);

	/**
	* @brief ゲームパッドの入力情報更新関数
	*/
	void UpdateGamePadState();

	/**
	* @biref XInput対応コントローラーの入力情報更新関数
	*/
	void UpdateXInput();

	/**
	* @biref ゲームパッド列挙用関数
	* ゲームパッドの初期化で使用する列挙関数です
	*/
	static BOOL CALLBACK EnumJoysticksCallback(const LPCDIDEVICEINSTANCE pdevins, LPVOID pContext);

	/**
	* @biref ゲームパッドのプロパティ設定関数
	* ゲームパッドの初期化で使用する、プロパティ設定用の関数です
	*/
	static bool SetGamePadPropaty(LPDIRECTINPUTDEVICE8 device);

	/**
	* @biref ゲームパッドの再起動関数
	* デバイスロストの際にゲームパッドの再起動を行う関数です
	*/
	bool RestartGamePad(LPDIRECTINPUTDEVICE8 device);

private:
	static const int m_Unresponsive_Range = 200;


	static LPDIRECTINPUT8 m_Interface;		//!< DirectInput8のインターフェイス
	LPDIRECTINPUTDEVICE8 m_KeyDevice;		//!< キーボード用デバイス
	LPDIRECTINPUTDEVICE8 m_MouseDevice;		//!< マウス用のデバイス
	LPDIRECTINPUTDEVICE8 m_GamePadDevice;	//!< ゲームパッド用のデバイス

	InputState m_KeyState[static_cast<int>(KeyInfo::Max_Key_Info)];			//!< キーボード入力情報
	int m_KeyInfo[static_cast<int>(KeyInfo::Max_Key_Info)] =
	{
	DIK_A,
	DIK_B,
	DIK_C,
	DIK_D,
	DIK_E,
	DIK_F,
	DIK_G,
	DIK_H,
	DIK_I,
	DIK_J,
	DIK_K,
	DIK_L,
	DIK_M,
	DIK_N,
	DIK_O,
	DIK_P,
	DIK_Q,
	DIK_R,
	DIK_S,
	DIK_T,
	DIK_U,
	DIK_V,
	DIK_W,
	DIK_X,
	DIK_Y,
	DIK_Z,
	DIK_UP,
	DIK_DOWN,
	DIK_RIGHT,
	DIK_LEFT,
	DIK_RETURN,
	DIK_ESCAPE,
	DIK_SPACE,
	DIK_1,
	DIK_2,
	DIK_3,
	DIK_4,
	DIK_5,
	DIK_6,
	DIK_7,
	DIK_8,
	DIK_9,
	DIK_0,
	};																		//!< キーボード割り当て情報

	InputState m_MouseState[3];		//!< マウス入力情報
	InputState m_GamePadState[static_cast<int>(XInput_Button::MAX_INFO)];		//!< ゲームパッド入力情報

	int m_InputState[static_cast<int>(InputInfo::Max_ID)];				//!< 入力情報

	InputMode m_InputMode;

	int m_MovementX;
	int m_MovementY;
	float m_MouseSensitivity;

};

#endif INPUT_MANAGER