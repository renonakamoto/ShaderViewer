#ifndef SEPIA_POST_EFFECT_H_
#define SEPIA_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"

/**
* @brief セピア処理を行うクラス
*/
class SepiaPostEffect : public PostEffectBase
{
private:
	/**
	* @brief セピアパラメータ構造体
	*/
	struct SepiaBuffer
	{
		float SpiaRate;		//! セピア率
		float Pad[3];		//! サイズを16の倍数に合わせるためのパディング

		SepiaBuffer()
		{
			ZeroMemory(this, sizeof(SepiaBuffer));
		}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	SepiaPostEffect(VertexShader* vs_, PixelShader* ps_) :
		PostEffectBase(vs_, ps_)
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~SepiaPostEffect()
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
	SepiaBuffer			 m_SepiaBuffer;		//! セピアパラメータ定数バッファ
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! 定数バッファ
};

#endif