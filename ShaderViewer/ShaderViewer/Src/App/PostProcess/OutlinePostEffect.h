﻿#ifndef OUTLINE_POST_EFFECT_H_
#define OUTLINE_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief アウトライン処理を行うクラス
*/
class OutlinePostEffect : public PostEffectBase
{
private:
	/**
	* @brief アウトラインパラメータ構造体
	*/
	struct OutlineBuffer
	{
		float Color[3];	//! アウトラインの色
		float Pad;		//! パディング

		/**
		* @brief コンストラクタ
		*/
		OutlineBuffer()
		{
			ZeroMemory(this, sizeof(OutlineBuffer));
		}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	OutlinePostEffect()
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~OutlinePostEffect()
	{}

	/**
	* @fn void Draw(const ViewModel& model_, const ViewModel* bgModel_)
	* @brief 描画関数
	* @param[in] model_ ビュー用モデル
	* @param[in] bgModel_ 背景用モデル
	*/
	void Draw(const ViewModel& model_, const ViewModel* bgModel_) override;

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
	OutlineBuffer		 m_OutlineBuffer;	//! アウトライン用構造体変数
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! コンストバッファ

};

#endif