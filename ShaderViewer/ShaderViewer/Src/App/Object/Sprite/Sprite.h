#ifndef SPRITE_H_
#define SPRITE_H_

#include "../../../Engine/Graphics/GraphicsUtility.h"
#include "../../../Engine/Shader/VertexShader.h"
#include "../../../Engine/Shader/PixelShader.h"
#include "../../../Utility/Vector/DXVector.h"

/**
* @brief スプライトクラス
*/
class Sprite
{
public:
	/**
	* @brief コンストラクタ
	*/
	Sprite():
		m_VertexShader(nullptr),
		m_PixelShader(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~Sprite()
	{}

	/**
	* @fn bool Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_)
	* @brief 初期化関数
	* @param[in] tex_		テクスチャデータ
	* @param[in] width_		横幅
	* @param[in] height_	縦幅
	* @param[in] vs_		頂点シェーダー
	* @param[in] ps_		ピクセルシェーダ
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool Init(ID3D11ShaderResourceView* tex_, UINT width_, UINT height_, VertexShader* vs_, PixelShader* ps_);
	
	/**
	* @fn void Drwa(DXVector3 pos_)
	* @brief 描画関数
	* @param[in] pos_ 描画座標(左上原点)
	*/
	void Draw(DXVector3 pos_);

private:
	/**
	* @fn bool CreateVertexBuffer()
	* @brief 頂点バッファ作成関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateVertexBuffer();

	/**
	* @fn bool CreateIndexBuffer()
	* @brief インデックスバッファ作成関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateIndexBuffer();

	/**
	* @fn bool CreateInoutLayout()
	* @brief 入力レイアウト作成関数
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateInoutLayout();
private:
	TextureData   m_TextureData;				//! テクスチャデータ
	VertexShader* m_VertexShader;				//! 頂点シェーダー
	PixelShader*  m_PixelShader;				//! ピクセルシェーダ
	ComPtr<ID3D11InputLayout> m_InputLayout;	//! 入力レイアウト
};

#endif