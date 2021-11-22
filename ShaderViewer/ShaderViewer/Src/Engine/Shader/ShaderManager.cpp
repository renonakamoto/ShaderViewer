#include "ShaderManager.h"
#include "../../Utility/Utility.h"
#include "../Engine.h"

bool ShaderManager::Load(const char* fileName_, std::string keyWord_, KindShader kindShader_)
{
	switch (kindShader_)
	{
	case KindShader::VS:
	{
		std::unique_ptr<VertexShader> entry_vs = LoadVS(fileName_);
		if (entry_vs) {
			entry_vs.swap(m_VertexShaders[keyWord_]);
			return true;
		}

		break;
	}
	case KindShader::PS:
	{
		std::unique_ptr<PixelShader> entry_ps = LoadPS(fileName_);
		if (entry_ps) {
			entry_ps.swap(m_PixelShaders[keyWord_]);
			return true;
		}

		break;
	}
	case KindShader::GS:
	{
		std::unique_ptr<GeometryShader> entry_gs = LoadGS(fileName_);
		if (entry_gs) {
			entry_gs.swap(m_GeometryShaders[keyWord_]);
			return true;
		}
		
		break;
	}
	default:
		break;
	}
	
	return false;
}

std::unique_ptr<VertexShader> ShaderManager::LoadVS(const char* fileName_)
{
	std::unique_ptr<VertexShader> vs = std::make_unique<VertexShader>();
	if (vs.get()->Create(GRAPHICS->GetDevice(), fileName_) == false) {
		vs.reset();
		return nullptr;
	}

	return vs;
}

std::unique_ptr<PixelShader> ShaderManager::LoadPS(const char* fileName_)
{
	std::unique_ptr<PixelShader> ps = std::make_unique<PixelShader>();
	if (ps.get()->Create(GRAPHICS->GetDevice(), fileName_) == false) {
		ps.reset();
		return nullptr;
	}

	return ps;
}

std::unique_ptr<GeometryShader> ShaderManager::LoadGS(const char* fileName_)
{
	std::unique_ptr<GeometryShader> gs = std::make_unique<GeometryShader>();
	if (gs.get()->Create(GRAPHICS->GetDevice(), fileName_) == false) {
		gs.reset();
		return nullptr;
	}

	return gs;
}
