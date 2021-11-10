#include "BlurPostEffect.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui.h"

void BlurPostEffect::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	// レンダーターゲットをオフスクリーンに設定
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);
	
	// シェーダーの設定
	LightingManager::GetInstance()->SetupShader();
	
	// モデルの描画
	model_.Render();

	// ポストエフェクト
	GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);
	GRAPHICS->GetContext()->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_BlurBuffer, 0U, 0U);
	GRAPHICS->GetContext()->PSSetConstantBuffers(0U, 1U, m_ConstantBuffer.GetAddressOf());
	m_ScreenSprite.Draw(DXVector3(0.0f, 0.0f, 0.0f));
}

void BlurPostEffect::DrawGUI()
{
	ImGui::SliderFloat("", &m_BlurBuffer.BlurStrength, 0.0f, 10.0f);
}

bool BlurPostEffect::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth			 = sizeof(BlurBuffer);
	buffer_desc.Usage				= D3D11_USAGE_DEFAULT;
	buffer_desc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
	buffer_desc.CPUAccessFlags		= 0U;
	buffer_desc.MiscFlags			= 0U;
	buffer_desc.StructureByteStride = 0U;

	ID3D11Device* device = GRAPHICS->GetDevice();

	if (FAILED(device->CreateBuffer(&buffer_desc, nullptr, m_ConstantBuffer.GetAddressOf())))
	{
		return false;
	}

	return true;
}
