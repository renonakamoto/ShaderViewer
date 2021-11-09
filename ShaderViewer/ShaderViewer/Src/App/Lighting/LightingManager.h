#ifndef LIGHTNG_MANAGER_H_
#define LIGHTNG_MANAGER_H_

#include <vector>
#include "LightingBase.h"

/**
* @brief Lighingオブジェクト管理クラス
*/
class LightingManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	LightingManager() :
		m_CurrentSelectShaderId(0)
	{}

	/**
	* @brief デストラクタ
	*/
	~LightingManager() {}

	/**
	* @fn static LightingManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return LightingManager* インスタンスのポインタ
	*/
	static LightingManager* GetInstance()
	{
		static LightingManager instance;
		return &instance;
	}

	/**
	* @fn void Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_)
	* @brief Lightingオブジェクトの登録関数
	* @param[in] displayName_ ディスプレイに表示させる名前
	* @param[in] lig_ Lightingオブジェクト
	*/
	void Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_);

	/**
	* @fn void SetUpShader()
	* @brief 選択されているシェーダーをセットする関数
	*/
	void SetupShader() const;
	
	/**
	* @fn void DrawGUI()
	* @brief 選択されているシェーダーのGUI描画関数
	*/
	void DrawGUI();

private:
	int m_CurrentSelectShaderId;								//! 現在選択されているシェーダーID
	std::vector<const char*>   m_LightingNamesList;				//! ライティング名リスト
	std::vector<std::unique_ptr<LightingBase>> m_LightingList;	//! ライティングリスト
};


#endif