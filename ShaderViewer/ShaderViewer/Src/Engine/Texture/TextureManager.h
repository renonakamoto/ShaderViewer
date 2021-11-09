#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include <D3D11.h>
#include <string>
#include <map>
#include "../Graphics/DirectGraphics.h"

/**
* @brief テクスチャ管理クラス
*/
class TextureManager
{
public:
	/**
	* @brief コンストラクタ
	*/
	TextureManager() :
		m_VertexShader(nullptr),
		m_PixelShader(nullptr),
		m_InputLayout(nullptr),
		m_ConstantBuffer(nullptr),
		m_SamplerState(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~TextureManager()
	{
		AllRelease();
	}
	
	/**
	* @fn bool Init(ID3D11Device* device_)
	* @brief 初期化関数
	* @param[in] device_ グラフィックデバイス
	* @return bool 成功したかどうかを真偽で返す
	* @details シェーダ、入力レイアウト、定数バッファの作成を行う
	*/
	bool Init(ID3D11Device* device_);

	/**
	* @fn bool Load(const char* fileName_, std::string keyword_)
	* @brief テクスチャ読み込み関数
	* @param[in] fileName_ ファイル名(パス付き)
	* @param[in] keyword_ テクスチャに紐づけるキーワード
	* @return bool 成功したかどうかを真偽で返す
	* @details 対応形式 : dds, tga, bmp, jpg, png
	*/
	bool Load(const char* fileName_, std::string keyword_);
	
	/**
	* @fn void Render(std::string keyword_, DirectX::XMFLOAT3 pos_)
	* @brief テクスチャ描画関数
	* @param[in] keyword_ ファイル名(パス付き)
	* @param[in] pos_ テクスチャに紐づいているキーワード
	*/
	void Render(std::string keyword_, DirectX::XMFLOAT3 pos_);

	/**
	* @fn TextureData* GetTexture(std::string keyword_)
	* @brief テクスチャ取得関数
	* @param[in] keyword_ テクスチャに紐づいているキーワード
	* @return TextureData* テクスチャデータのポインタ
	*/
	TextureData* GetTexture(std::string keyword_) { 
		if (m_Textures.find(keyword_) == m_Textures.end()) return nullptr;
		return &m_Textures[keyword_];
	}

	/**
	* @fn void Release(std::string keyword_)
	* @brief 指定したテクスチャを削除する関数
	* @param[in] keyword_ テクスチャに紐づいているキーワード
	*/
	void Release(std::string keyword_);

	/**
	* @fn void AllRelease()
	* @brief 保存されているテクスチャをすべて解放する関数
	*/
	void AllRelease();
	
private:
	/**
	* @fn bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief 頂点バッファの作成関数
	* @param[in] data_ テクスチャデータ
	* @param[in] device_ グラフィックデバイス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateVertexBuffer(TextureData& data_, ID3D11Device* device_);

	/**
	* @fn bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_)
	* @brief インデックスバッファの作成関数
	* @param[in] data_ テクスチャデータ
	* @param[in] device_ グラフィックデバイス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateIndexBuffer(TextureData& data_, ID3D11Device* device_);

private:

	/**
	* @fn bool CreateConstantBuffer(ID3D11Device* device_)
	* @brief 定数バッファの作成関数
	* @param[in] device_ グラフィックデバイス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateConstantBuffer(ID3D11Device* device_);

	/**
	* @fn bool CreateSamplerState(ID3D11Device* device_)
	* @brief テクスチャサンプラーの作成関数
	* @param[in] device_ グラフィックデバイス
	* @return bool 成功したかどうかを真偽で返す
	*/
	bool CreateSamplerState(ID3D11Device* device_);

private:
	std::map<std::string, TextureData>  m_Textures;				//! テクスチャ保存用マップ
	std::unique_ptr<VertexShader>		m_VertexShader;			//! 頂点シェーダー
	std::unique_ptr<PixelShader>		m_PixelShader;			//! ピクセルシェーダ
	ComPtr<ID3D11InputLayout>			m_InputLayout;			//! 入力レイアウト
	ComPtr<ID3D11SamplerState>			m_SamplerState;			//! サンプラーステート
	ComPtr<ID3D11Buffer>				m_ConstantBuffer;		//! 定数バッファオブジェクト
	ConstantBuffer2D					m_ConstantBufferData;	//! 定数バッファ

};

#endif