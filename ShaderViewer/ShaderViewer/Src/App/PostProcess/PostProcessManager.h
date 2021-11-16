#ifndef POST_PROCESS_MANAGERE_H_
#define POST_PROCESS_MANAGERE_H_

#include "../ViewModel/ViewModel.h"
#include "PostEffectBase.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief ポストプロセスの管理を行うクラス
*/
class PostProcessManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	PostProcessManager():
		m_CurrentID(0)
	{}

	/**
	* @brief デストラクタ
	*/
	~PostProcessManager()
	{}

	/**
	* @fn void Entry(const char* displayName_, std::string vsKey_, std::string psKey_)
	* @brief ポストエフェクトオブジェクトの登録関数
	* @param[in] displayName_ ディスプレイに表示させる名前
	* @param[in] vsKey_ バーテックスシェーダーのキー
	* @param[in] psKey_ ピクセルシェーダーのキー
	*/
	template<class T>
	bool Entry(const char* displayName_, std::string vsKey_, std::string psKey_);

	/**
	* @fn void Draw(const ViewModel& model_, const ViewModel* bgModel_)
	* @brief 描画関数
	* @param[in] model_ ビュー用モデル
	* @param[in] bgModel_ 背景用モデル
	*/
	void Draw(const ViewModel& model_, const ViewModel* bgModel_);
	
	/**
	* @fn void DrawGUI()
	* @brief GUI描画関数
	*/
	void DrawGUI();

private:
	std::vector<std::unique_ptr<PostEffectBase>> m_PostEffectList;		//! ポストエフェクトリスト
	std::vector<const char*>					 m_PostEffectNameList;	//! ポストエフェクト名リスト
	int											 m_CurrentID;			//! 現在のID
};

template<class T>
inline bool PostProcessManager::Entry(const char* displayName_, std::string vsKey_, std::string psKey_)
{
	std::unique_ptr<PostEffectBase> pp = std::make_unique<T>();
	auto shader_manager = ShaderManager::GetInstance();
	bool succeed = pp.get()->Init(shader_manager->GetVertexShader(vsKey_), shader_manager->GetPixelShader(psKey_));

	if (!succeed)
	{
		return false;
	}

	m_PostEffectList.push_back(std::move(pp));
	m_PostEffectNameList.push_back(displayName_);

	return true;
}


#endif