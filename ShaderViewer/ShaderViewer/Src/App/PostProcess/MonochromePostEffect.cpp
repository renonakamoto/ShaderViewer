#include "MonochromePostEffect.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"

void MonochromePostEffect::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	// レンダーターゲットをオフスクリーンに設定
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);

	// シェーダーの設定
	LightingManager::GetInstance()->SetupShader();

	// モデルの描画
	model_.Render();

	// ポストエフェクト
	GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);
	m_ScreenSprite.Draw(DXVector3(0.0f, 0.0f, 0.0f));
}

void MonochromePostEffect::DrawGUI()
{
}
