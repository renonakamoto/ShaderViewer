#include "LightingManager.h"
#include "../Config.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void LightingManager::SetupShader() const
{
	if (m_LightingList.size() == 0) {
		return;
	}

	m_LightingList[m_CurrentSelectShaderId]->SetUpShader();
	
}

void LightingManager::DrawGUI()
{
	if (m_LightingList.size() == 0) {
		return;
	}

	float window_width  = static_cast<float>(WINDOW->GetClientWidth());
	float window_height = static_cast<float>(WINDOW->GetClientHeight());
	
	ImGui::SetNextWindowPos(ImVec2(0.0f, window_height/3.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, ConfigParameter::m_GuiHeight), ImGuiCond_Always);
	ImGui::Begin("ShaderList");
	ImGui::Separator();
	ImGui::Text("List");
	ImGui::ListBox("", &m_CurrentSelectShaderId, m_LightingNamesList.data(), static_cast<int>(m_LightingNamesList.size()));
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(window_width - ConfigParameter::m_GuiWidth, window_height / 3.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, ConfigParameter::m_GuiHeight), ImGuiCond_Always);
	ImGui::Begin("ShaderParam");
	m_LightingList[m_CurrentSelectShaderId]->DrawGUI();
	ImGui::End();
}
