#ifndef BLUR_POST_EFFECT_H_
#define BLUR_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief ブラー処理を行うクラス
*/
class BlurPostEffect : public PostEffectBase
{
private:
	/**
	* @brief ブラーパラメータ用構造体
	*/
	struct BlurBuffer
	{
		float BlurStrength;	//! ブラーの強さ
		float Pad[3];		//! サイズを16の倍数に合わせるためのパディング

		/**
		* @brief コンストラクタ
		*/
		BlurBuffer()
		{
			ZeroMemory(this, sizeof(BlurBuffer));
		}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	BlurPostEffect()
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~BlurPostEffect()
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

private:
	/**
	* @fn bool CreateConstantBuffer()
	* @brief 定数バッファ作成関数
	* @return bool 成功したかどうか
	*/
	bool CreateConstantBuffer();

private:
	BlurBuffer			 m_BlurBuffer;		//! ブラーパラメータの定数バッファ
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! 定数バッファ
};

#endif