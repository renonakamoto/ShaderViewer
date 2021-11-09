#ifndef PIXELSHADER_H_
#define PIXELSHADER_H_

#include <d3d11.h>
#include <wrl.h>
#include "ShaderBase.h"


/**
* @brief ピクセルシェーダ扱うクラス
*/
class PixelShader : public ShaderBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	PixelShader():
		m_Interface(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~PixelShader() final
	{}

	/**
	* @fn bool Create(ID3D11Device* device_, const char* fileName_))
	* @brief ピクセルシェーダシェーダーの作成を行う関数
	* @param[in] device_ デバイス
	* @param[in] fileName_ ファイル名(パス付)
	* @return bool 成功したかどうかを真偽で返す
	* @details すでにコンパイルされているcsoファイルを指定する
	*/
	bool Create(ID3D11Device* device_, const char* fileName_)override;

	/**
	* @fn ID3D11VertexShader* GetShaderInterface()
	* @brief シェーダーのインターフェースを返す関数
	* @return ID3D11VertexShader* インターフェースのポインタ
	*/
	ID3D11PixelShader* GetShaderInterface()
	{
		return m_Interface.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_Interface;	//! ピクセルシェーダーインターフェース
};

#endif