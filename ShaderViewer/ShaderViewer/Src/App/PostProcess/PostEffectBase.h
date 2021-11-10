#ifndef PostEffectBase_H_
#define PostEffectBase_H_

#include "../ViewModel/ViewModel.h"
#include "../../Engine/Engine.h"
#include "../Object/Sprite/Sprite.h"


/**
* @brief ポストエッフェクトの基底クラス
*/
class PostEffectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	PostEffectBase()
	{}

	/**
	* @brief デストラクタ
	*/
	~PostEffectBase()
	{}

	/**
	* @fn bool Init(VertexShader* vs_, PixelShader* ps_)
	* @brief 初期化関数
	* @param[in] vs_ 頂点シェーダー
	* @param[in] ps_ ピクセルシェーダー
	* @return bool 成功したかどうか
	*/
	bool Init(VertexShader* vs_, PixelShader* ps_);

	/**
	* @fn virtual void Render(const ViewModel& model_, const ViewModel* bgModel_) = 0
	* @brief 描画関数
	* @param[in] model_ ビュー用モデル
	* @param[in] bgModel_ 背景用モデル
	*/
	virtual void Render(const ViewModel& model_, const ViewModel* bgModel_) = 0;
	
	/**
	* @fn virtual void DrawGUI() = 0
	* @brief GUI描画関数
	*/
	virtual void DrawGUI() = 0;

protected:
	Sprite m_ScreenSprite;	//! シーンスプライト

};

#endif