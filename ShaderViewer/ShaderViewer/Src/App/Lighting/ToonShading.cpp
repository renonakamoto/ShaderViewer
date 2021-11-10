#include "ToonShading.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Engine.h"

ToonShading::ToonShading()
{
	TEX_MANAGER->Load("Assets/Textures/Ramp.png", "Ramp");
}

void ToonShading::SetUpShader() const
{
	ID3D11DeviceContext* context = GRAPHICS->GetContext();
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(m_PixelShader->GetShaderInterface(), nullptr, 0U);

	ID3D11ShaderResourceView* tex = TEX_MANAGER->GetTexture("Ramp")->Texture.Get();
	context->PSSetShaderResources(1U, 1U, &tex);
}

void ToonShading::DrawGUI()
{
}