#ifndef LIGHTNG_MANAGER_H_
#define LIGHTNG_MANAGER_H_


#include "LightingBase.h"
#include "../../Engine/Shader/ShaderManager.h"
#include <vector>
#include <string>

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
	* @fn void Entry(const char* displayName_, std::string vsKey_, std::string psKey_)
	* @brief Lightingオブジェクトの登録関数
	* @param[in] displayName_ ディスプレイに表示させる名前
	* @param[in] vsKey_ バーテックスシェーダーのキー
	* @param[in] psKey_ ピクセルシェーダーのキー
	*/
	template<class T>
	bool Entry(const char* displayName_, std::string vsKey_, std::string psKey_);

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


template<class T>
inline bool LightingManager::Entry(const char* displayName_, std::string vsKey_, std::string psKey_)
{
	std::unique_ptr<LightingBase> lig = std::make_unique<T>();
	auto shader_manager = ShaderManager::GetInstance();
	bool succeed = lig.get()->Init(shader_manager->GetVertexShader(vsKey_), shader_manager->GetPixelShader(psKey_));

	if (!succeed)
	{
		return false;
	}

	m_LightingList.push_back(std::move(lig));
	m_LightingNamesList.push_back(displayName_);

	return true;
}


#endif