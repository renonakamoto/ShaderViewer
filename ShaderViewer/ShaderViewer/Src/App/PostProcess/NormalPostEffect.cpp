#include "NormalPostEffect.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"

void NormalPostEffect::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);
	LightingManager::GetInstance()->SetupShader();
	
	// モデルの描画
	model_.Render();

	GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);
	m_ScreenSprite.Draw(DXVector3(0.0f, 0.0f, 0.0f));
}

void NormalPostEffect::DrawGUI()
{
}