#ifndef MONOCHROME_POST_EFFECT_H_
#define MONOCHROME_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief モノクロ処理を行うクラス
*/
class MonochromePostEffect : public PostEffectBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	MonochromePostEffect()
	{}

	/**
	* @brief デストラクタ
	*/
	~MonochromePostEffect()
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