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
	PostEffectBase(VertexShader* vs_, PixelShader* ps_)
	{
		m_ScreenSprite.Init(
			GRAPHICS->GetRenderTarget(KindRT::RT_OFF_SCREEN)->GetTexture(),
			WINDOW->GetClientWidth(),
			WINDOW->GetClientHeight(),
			vs_,
			ps_
		);
	}

	/**
	* @brief デストラクタ
	*/
	~PostEffectBase()
	{}

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