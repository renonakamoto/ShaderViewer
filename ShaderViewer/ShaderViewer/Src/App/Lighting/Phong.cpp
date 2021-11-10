#include "Phong.h"
#include "../../Engine/imGui/imgui.h"
#include "../../Engine/Engine.h"

void Phong::SetUpShader() const
{
	ID3D11DeviceContext* context = GRAPHICS->GetContext();
	context->VSSetShader(m_VertexShader->GetShaderInterface(), nullptr, 0U);
	context->PSSetShader(m_PixelShader->GetShaderInterface(),  nullptr, 0U);
	context->UpdateSubresource(m_ConstantBuffer.Get(), 0U, nullptr, &m_PhongBuffer, 0U, 0U);
	context->PSSetConstantBuffers(1U, 1U, m_ConstantBuffer.GetAddressOf());
}

void Phong::DrawGUI()
{
	ImGui::SliderFloat("", &m_PhongBuffer.Shininess, m_MinShiness, m_MaxShiness);
}

bool Phong::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC buffer_desc;
	ZeroMemory(&buffer_desc, sizeof(buffer_desc));
	buffer_desc.ByteWidth			= sizeof(PhongBuffer);
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
