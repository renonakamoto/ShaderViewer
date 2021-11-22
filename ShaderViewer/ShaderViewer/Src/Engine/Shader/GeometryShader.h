#ifndef GEOMETRY_SHADER_H_
#define GEOMETRY_SHADER_H_

#include <d3d11.h>
#include <wrl.h>
#include "ShaderBase.h"


/**
* @brief ジオメトリーシェーダ扱うクラス
*/
class GeometryShader : public ShaderBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	GeometryShader() :
		m_Interface(nullptr)
	{}

	/**
	* @brief デストラクタ
	*/
	~GeometryShader() final
	{}

	/**
	* @fn bool Create(ID3D11Device* device_, const char* fileName_))
	* @brief ジオメトリーシェーダーの作成を行う関数
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
	ID3D11GeometryShader* GetShaderInterface()
	{
		return m_Interface.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_Interface;	//! ピクセルシェーダーインターフェース
};

#endif