#ifndef BLINN_PHONG_H_
#define BLINN_PHONG_H_

#include "LightingBase.h"

/**
* @brief BlinnPhongシェーディングクラス
*/
class BlinnPhong : public LightingBase
{
private:
	/**
	* @brief BlinnPhong用構造体
	*/
	struct BlinnPhongBuffer
	{
		float Shininess;	//! ハイライトの強さ(低いほど強く光る)
		float Pad[3];		//! サイズを16の倍数に合わせるためのパディング
		
		/**
		* @brief コンストラクタ
		*/
		BlinnPhongBuffer():
			Shininess(0.f),
			Pad{20.f}
		{}
	};

public:
	/**
	* @brief コンストラクタ
	*/
	BlinnPhong() :
		m_BlinnPhongBuffer{}
	{
		CreateConstantBuffer();
	}

	/**
	* @brief デストラクタ
	*/
	~BlinnPhong()
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
	BlinnPhongBuffer	 m_BlinnPhongBuffer;	//! BlinnPhong用構造体変数
	ComPtr<ID3D11Buffer> m_ConstantBuffer;		//! コンストバッファ
};

#endif