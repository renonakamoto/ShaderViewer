#ifndef NORMAL_POST_EFFECT_H_
#define NORMAL_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief 通常描画処理を行うクラス
*/
class NormalPostEffect : public PostEffectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	NormalPostEffect(VertexShader* vs_, PixelShader* ps_) :
		PostEffectBase(vs_, ps_)
	{}

	/**
	* @brief デストラクタ
	*/
	~NormalPostEffect()
	{}

	/**
	* @fn void Render(const ViewModel& model_, const ViewModel* bgModel_)
	* @brief 描画関数
	* @param[in] model_ ビュー用モデル
	* @param[in] bgModel_ 背景用モデル
	*/
	void Render(const ViewModel& model_, const ViewModel* bgModel_) override;

	/**
	* @fn void DrawGUI()
	* @brief GUI描画関数
	*/
	void DrawGUI() override;

};

#endif