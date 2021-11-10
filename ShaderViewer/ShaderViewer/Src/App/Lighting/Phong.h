#ifndef PHONG_H_
#define PHONG_H_

#include "LightingBase.h"

/**
* @brief PhongShadingクラス
*/
class Phong : public LightingBase
{
private:
	/**
	* @brief フォンパラメータ構造体
	*/
	struct PhongBuffer
	{
		float Shininess;	//! ハイライトの強さ(低いほど強く光る)
		float Pad[3];		//! サイズを16の倍数に合わせるためのパディング

		/**
		* @brief コンストラクタ
		*/
		PhongBuffer():
			Shininess(20.f),
			Pad{0.f}
		{}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	Phong() :
		m_MinShiness(5.f),
		m_MaxShiness(200.f)
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~Phong()
	{}

	/**
	* @fn void SetUpShader()
	* @brief シェーダーセット関数
	*/
	void SetUpShader() const override;

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
	PhongBuffer			 m_PhongBuffer;		//! フォン用構造体変数
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! コンストバッファ
	const float			 m_MinShiness;		//! ハイライトの強さの最小値
	const float			 m_MaxShiness;		//! ハイライトの強さの最大値
};

#endif