#ifndef SHADER_BASE_H_
#define SHADER_BASE_H_

#include <d3d11.h>


/**
* @brief シェーダーの基底クラス
*/
class ShaderBase
{
public:
	/**
	* @brief コンストラクタ
	*/
	ShaderBase():
		m_Data(nullptr),
		m_Size(0)
	{}

	/**
	* @brief デストラクタ
	*/
	virtual ~ShaderBase()
	{
		if (m_Data)
		{
			delete[] m_Data;
		}
	}

	/**
	* @fn bool Create(ID3D11Device* device_, const char* fileName_)
	* @brief シェーダーの作成を行う関数
	* @param[in] device_ デバイス
	* @param[in] fileName_ ファイル名(パス付)
	* @return bool 成功したかどうかを真偽で返す
	* @details すでにコンパイルされているcsoファイルを指定する
	*/
	virtual bool Create(ID3D11Device* device_, const char* fileName_);

	/**
	* @fn const char* GetData()
	* @brief シェーダーのバイナリデータの取得関数
	* @return const char* シェーダーのバイナリデータ
	*/
	const char* GetData()
	{
		return m_Data;
	}

	/**
	* @fn long GetSize()
	* @brief シェーダーのサイズの取得関数
	* @return long シェーダーのサイズ
	*/
	long GetSize() { return m_Size; }

private:
	/**
	* @fn int LoadFile(const char* fileName_)
	* @brief シェーダーの読み込み関数
	* @param[in] fileName_ ファイル名(パス付)
	* @return int 読み込んだシェーダーのサイズ
	* @details バイナリデータとサイズを取得する
	*/
	int LoadFile(const char* fileName_);

protected:
	char* m_Data;	//! シェーダーのバイナリデータ
	long  m_Size;	//! シェーダーのサイズ
};

#endif