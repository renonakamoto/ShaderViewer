
#include <d3dcompiler.h>
#include "LightingBase.h"
#include "../../Engine/Engine.h"

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

bool LightingBase::Init(VertexShader* vertexShader_, PixelShader* pixelShader_)
{
	m_VertexShader = vertexShader_;
	m_PixelShader  = pixelShader_;

    return true;
}