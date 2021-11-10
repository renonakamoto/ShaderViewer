#ifndef CONFIG_H_
#define CONFIG_H_

#include "../Utility/Vector/DXVector.h"

/**
* @brief 設定パラメータを保持するクラス
*/
class ConfigParameter
{
public:
	/**
	* @fn void Load()
	* @brief Configデータの読み込み関数
	*/
	static void Load();

public:
	static float m_CameraFov;	//! カメラ視野
	static float m_CameraNear;	//! カメラnear
	static float m_CameraFar;	//! カメラfar

	static float m_GuiWidth;	//! GUIの横幅
	static float m_GuiHeight;	//! GUIの縦幅

	static DXVector3 m_LightPos;//! ライトの座標
};

#endif