#include "ViewModel.h"
#include "../Config.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void ViewModel::Update()
{
	if (m_Rotate)
	{
		m_Rot.y += 0.5f;
	}
}

void ViewModel::Render() const
{
	if (m_ObjModel) {
		GRAPHICS->SetRasterizerMode(RasterizerMode::MODE_CULL_NONE);
		GRAPHICS->GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_ObjModel->Render(m_Pos, m_Scale, m_Rot);
	}
}

void ViewModel::DrawGUI()
{
	float window_width  = WINDOW->GetClientWidth();

	ImGui::SetNextWindowPos(ImVec2(window_width - ConfigParameter::m_GuiWidth, 0.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, ConfigParameter::m_GuiHeight), ImGuiCond_Always);
	ImGui::Begin("TransForm");
	ImGui::Separator();
	ImGui::DragFloat3("Pos", &m_Pos.x, 0.01f);
	ImGui::DragFloat3("Sca", &m_Scale.x, 0.01f);
	ImGui::DragFloat3("Rot", &m_Rot.x,0.5f);
	ImGui::Checkbox("Rotate", &m_Rotate);
	ImGui::End();
}