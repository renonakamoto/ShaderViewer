#include "OutlinePostEffect.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui.h"

void OutlinePostEffect::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	// モデルをオフスクリーンに描画
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);
	LightingManager::GetInstance()->SetupShader();

	model_.Render();

	// シャドウマップに深度値を描画
	GRAPHICS->ClearRenderTarget(KindRT::RT_SHADOWMAP);
	GRAPHICS->SetRenderTarget(KindRT::RT_SHADOWMAP);
	// シャドウマップ用のシェーダーをセットする
	ID3D11DeviceContext* context = GRAPHICS->GetContext();
	context->VSSetShader(ShaderManager::GetInstance()->GetVertexShader("CameraDepthVS")->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(ShaderManager::GetInstance()->GetPixelShader("DepthPS")->GetShaderInterface(), nullptr, 0U);
	model_.Render();
	
	const int bg_model_num = 2;
	for (int i = 0; i < bg_model_num; ++i)
	{
		if (&bgModel_[i] == nullptr) {
			bgModel_[i].Render();
		}
	}

	// ポストエフェクト
	GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);
	ID3D11ShaderResourceView* depth_tex = GRAPHICS->GetRenderTarget(KindRT::RT_SHADOWMAP)->GetTexture();
	GRAPHICS->GetContext()->PSSetShaderResources(1U, 1U, &depth_tex);
	GRAPHICS->GetContext()->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_OutlineBuffer, 0U, 0U);
	GRAPHICS->GetContext()->PSSetConstantBuffers(0U, 1U, m_ConstantBuffer.GetAddressOf());
	m_ScreenSprite.Draw(DXVector3(0.0f, 0.0f, 0.0f));
}

void OutlinePostEffect::DrawGUI()
{
	ImGui::DragFloat3("", m_OutlineBuffer.Color, 0.01f, 0.0f, 1.0f);
	ImGui::Separator();
	ImGui::ColorPicker3("", m_OutlineBuffer.Color);
}

bool OutlinePostEffect::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth			= sizeof(OutlineBuffer);
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
