#ifndef TOON_SHADING_H_
#define TOON_SHADING_H_

#include "LightingBase.h"

/**
* @brief ToonShaderクラス
*/
class ToonShading : public LightingBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	ToonShading();

	/**
	* @brief デストラクタ
	*/
	~ToonShading()
	{}

	/**
	* @fn void SetUpShader()
	* @brief シェーダーセット関数
	*/
	void SetUpShader() const override;

	/**
	* @fn void DrawGUI()
	* @brief 描画GUI関数
	*/
	void DrawGUI() override;

};

#endif