#ifndef LIGHTING_BASE_H_
#define LIGHTING_BASE_H_

#include <memory>
#include <wrl.h>
#include "../../Engine/Shader/VertexShader.h"
#include "../../Engine/Shader/PixelShader.h"

using namespace Microsoft::WRL;

/**
* @brief ライティング基底クラス
*/
class LightingBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	LightingBase():
		m_VertexShader(nullptr),
		m_PixelShader(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~LightingBase()
	{}
	
	/**
	* @fn bool Init(VertexShader* vertexShader_, PixelShader* pixelShader_)
	* @brief 初期化関数
	* @param[in] vertexShader_ 頂点シェーダ
	* @param[in] pixelShader_ ピクセルシェーダ
	*/
	bool Init(VertexShader* vertexShader_, PixelShader* pixelShader_);
	
	/**
	* @fn void SetUpShader()
	* @brief シェーダー設定関数
	*/
	virtual void SetUpShader() const = 0;

	/**
	* @fn void DrawGUI()
	* @brief GUI描画関数
	*/
	virtual void DrawGUI() = 0;
	
protected:
	VertexShader*			  m_VertexShader;	//! 頂点シェーダー
	PixelShader*			  m_PixelShader;	//! ピクセルシェーダー

};

#endif