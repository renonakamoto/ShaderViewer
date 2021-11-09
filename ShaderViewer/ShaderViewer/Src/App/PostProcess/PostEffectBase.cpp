#include "PostEffectBase.h"

bool PostEffectBase::Init(VertexShader* vs_, PixelShader* ps_)
{
	bool successed = m_ScreenSprite.Init(
		GRAPHICS->GetRenderTarget(KindRT::RT_OFF_SCREEN)->GetTexture(),
		WINDOW->GetClientWidth(),
		WINDOW->GetClientHeight(),
		vs_,
		ps_
	);

	return successed;
}