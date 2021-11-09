#ifndef SHADER_MANAGER_H_
#define SHADER_MANAGER_H_

#include <unordered_map>
#include <string>
#include <memory>
#include "VertexShader.h"
#include "PixelShader.h"

enum class KindShader
{
	VS,
	PS,
};

class ShaderManager
{
public:
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
	ShaderManager() {}

	~ShaderManager() {}

private:
	std::unique_ptr<VertexShader> LoadVS(const char* fileName_);
	std::unique_ptr<PixelShader>  LoadPS(const char* fileName_);

private:
	std::unordered_map<std::string, std::unique_ptr<VertexShader>> m_VertexShaders;	// 頂点シェーダーマップ
	std::unordered_map<std::string, std::unique_ptr<PixelShader>>  m_PixelShaders;	// ピクセルシェーダーマップ
	
};

#endif