#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "VertexShader.h"
#include "PixelShader.h"
#include "GeometryShader.h"

enum class KindShader
{
	VS,	//! バーテックスシェーダー
	PS,	//! ピクセルシェーダ
	GS,	//! ジオメトリーシェーダー
};

/**
* @brief シェーダーを管理するクラス
*/
class ShaderManager
{
public:
	/**
	* @fn static ShaderManager* GetInstance()
	* @brief インスタンスを返す関数
	* @return ShaderManager* インスタンスのポインタ
	*/
	static ShaderManager* GetInstance()
	{
		static ShaderManager instance;
		return &instance;
	}

	bool Load(const char* fileName_, std::string keyWord_, KindShader kindShader_);

	inline VertexShader* GetVertexShader(std::string keyWord_) 
	{
		if (m_VertexShaders.find(keyWord_) == m_VertexShaders.end()) {
			return nullptr;
		}
		return m_VertexShaders[keyWord_].get();
	}
	
	inline PixelShader*  GetPixelShader(std::string keyWord_)
	{
		if (m_PixelShaders.find(keyWord_) == m_PixelShaders.end()) {
			return nullptr;
		}
		return m_PixelShaders[keyWord_].get();
	}


private:
	/**
	* @brief コンストラクタ
	*/
	ShaderManager() {}

	/**
	* @brief デストラクタ
	*/
	~ShaderManager() {}

private:
	std::unique_ptr<VertexShader> LoadVS(const char* fileName_);
	std::unique_ptr<PixelShader>  LoadPS(const char* fileName_);
	std::unique_ptr<GeometryShader>  LoadGS(const char* fileName_);

private:
	std::unordered_map<std::string, std::unique_ptr<VertexShader>>	  m_VertexShaders;		//! 頂点シェーダー
	std::unordered_map<std::string, std::unique_ptr<PixelShader>>	  m_PixelShaders;		//! ピクセルシェーダー
	std::unordered_map<std::string, std::unique_ptr<GeometryShader>>  m_GeometryShaders;	//! ジオメトリーシェーダー
	
};

#endif