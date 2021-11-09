#ifndef VERTEX_SHADER_H_
#define VERTEX_SHADER_H_

#include <d3d11.h>
#include <wrl.h>
#include "ShaderBase.h"


/**
* @brief バーテックスシェーダーを扱うクラス
*/
class VertexShader : public ShaderBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	VertexShader() :
		m_Interface(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~VertexShader() final
	{}

	/**
	* @fn bool Create(ID3D11Device* device_, const char* fileName_))
	* @brief バーテックスシェーダーの作成を行う関数
	* @param[in] device_ デバイス
	* @param[in] fileName_ ファイル名(パス付)
	* @return bool 成功したかどうかを真偽で返す
	* @details すでにコンパイルされているcsoファイルを指定する
	*/
	bool Create(ID3D11Device* device_, const char* fileName_) override;

	/**
	* @fn ID3D11VertexShader* GetShaderInterface()
	* @brief シェーダーのインターフェースを返す関数
	* @return ID3D11VertexShader* インターフェースのポインタ
	*/
	ID3D11VertexShader* GetShaderInterface()
	{
		return m_Interface.Get();
	}

	/**
	* @fn ID3D11InputLayout* GetInputLayout()
	* @brief 入力レイアウトを返す関数
	* @return ID3D11InputLayout* 入力レイアウトのポインタ
	*/
	ID3D11InputLayout* GetInputLayout()
	{
		return m_InputLayout.Get();
	}

private:
	/**
	* @fn bool CreateInputLayout(ID3D11Device* device_)
	* @brief 入力レイアウトの作成関数
	* @param[in] device_ グラフィックデバイス
	*/
	bool CreateInputLayout(ID3D11Device* device_);

	DXGI_FORMAT GetDxgiFormat(D3D10_REGISTER_COMPONENT_TYPE type_, BYTE mask_);

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_Interface;	 //! バーテックスシェーダーインターフェース
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_InputLayout; //! 入力レイアウト

};

#endif