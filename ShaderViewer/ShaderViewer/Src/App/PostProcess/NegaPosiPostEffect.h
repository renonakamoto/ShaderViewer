#ifndef NEGAPOSI_POST_EFFECT_H_
#define NEGAPOSI_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief ネガポジ反転処理を行うクラス
*/
class NegaPosiPostEffect : public PostEffectBase
{
private:
	/**
	* @brief ネガポジパラメータ構造体
	*/
	struct NegaBuffer
	{
		float NegaRate;		//! ネガポジ反転率
		float Pad[3];		//! サイズを16の倍数に合わせるためのパディング

		/**
		* @brief ネガポジパラメータ構造体
		*/
		NegaBuffer()
		{
			ZeroMemory(this, sizeof(NegaBuffer));
		}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	NegaPosiPostEffect()
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~NegaPosiPostEffect()
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
	NegaBuffer			 m_NegaBuffer;		//! ネガポジ用構造体変数
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! コンストバッファ
};

#endif