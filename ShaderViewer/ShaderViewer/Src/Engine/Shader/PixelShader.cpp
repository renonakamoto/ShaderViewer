#include "PixelShader.h"

bool PixelShader::Create(ID3D11Device* device_, const char* fileName_)
{
	if (ShaderBase::Create(device_, fileName_) == false)
	{
		return false;
	}

	if (FAILED(device_->CreatePixelShader(m_Data, m_Size, nullptr, m_Interface.GetAddressOf())))
	{
		return false;
	}

	return true;
}