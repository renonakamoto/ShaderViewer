#ifndef APP_H_
#define APP_H_

#include "Camera/Camera.h"
#include "ViewModel/ViewModelManager.h"
#include "Lighting/LightingManager.h"
#include "PostProcess/NormalPostEffect.h"
#include "PostProcess/BlurPostEffect.h"
#include "PostProcess/PostProcessManager.h"
#include "Object/SkyDome/SkyDome.h"
#include "Object/Plane/Plane.h"

/**
* @brief アプリの制御クラス
*/
class App
{
public:
	/**
	* @fn static App* GetInstance()
	* @brief インスタンスを返す関数
	* @return App* インスタンスのポインタ
	*/
	static App* GetInstance()
	{
		static App instance;
		return &instance;
	}

	/**
	* @fn bool Init()
	* @brief アプリケーションの初期化を行う関数
	* @return bool 成功したかどうか
	*/
	bool Init();

	/**
	* @fn void Run()
	* @brief 実行関数
	* @details アプリケーションの更新と描画を行う
	*/
	void Run();

private:
	/**
	* @fn void Update()
	* @brief アプリケーションの更新を行う関数
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief アプリケーションの描画を行う関数
	*/
	void Render();

	/**
	* @fn void SetUpDepthShader()
	* @brief シャドウマップの設定を行う関数
	*/
	void SetUpDepthShader();

	/**
	* @fn void SetUpUnlitShader()
	* @brief アンリット描画設定を行う関数
	*/
	void SetUpUnlitShader();

	/**
	* @fn void DrawDepth()
	* @brief シャドウマップの描画を行う関数
	*/
	void DrawDepth();

private:
	/**
	* @fn bool InitModels()
	* @brief モデルの初期化関数
	* @return bool 成功したかどうか
	*/
	bool InitModels();

	/**
	* @fn bool InitShader()
	* @brief シェーダーの初期化関数
	* @return bool 成功したかどうか
	*/
	bool InitShaders();

	/**
	* @fn bool InitLigtings()
	* @brief ライティングの初期化関数
	* @return bool 成功したかどうか
	*/
	bool InitLigtings();

	/**
	* @fn bool InitPostProcess()
	* @brief ポストプロセスの初期化関数
	*/
	void InitPostProcess();

private:
	/**
	* @brief コンストラクタ
	*/
	App()
	{}

	/**
	* @brief デストラクタ
	*/
	~App()
	{}

private:
	std::unique_ptr<Camera>	 m_Camera;				//! カメラ
	ViewModelManager		 m_ModelManager;		//! モデルマネージャ	
	PostProcessManager		 m_PostProcessManager;	//! ポストプロセスマネージャ

	// 背景オブジェクト
	SkyDome m_SkyDome;	//! スカイドーム
	Plane   m_Plane;	//! プレーン
};

#define APP App::GetInstance()

#endif