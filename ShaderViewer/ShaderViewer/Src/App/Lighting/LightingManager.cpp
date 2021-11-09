#include "LightingManager.h"
#include "../Definition.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void LightingManager::Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_)
{
	if(!lig_) {
		return;
	}

	m_LightingNamesList.push_back(displayName_);
	m_LightingList.push_back(std::move(lig_));
}

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

	float window_width  = WINDOW->GetClientWidth();
	float window_height = WINDOW->GetClientHeight();
	
	ImGui::SetNextWindowPos(ImVec2(0.0f, window_height/3.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, GUI_HEIGHT), ImGuiCond_Always);
	ImGui::Begin("ShaderList");
	ImGui::Separator();
	ImGui::Text("List");
	ImGui::ListBox("", &m_CurrentSelectShaderId, m_LightingNamesList.data(), static_cast<int>(m_LightingNamesList.size()));
	ImGui::End();
	
	ImGui::SetNextWindowPos(ImVec2(window_width - GUI_WIDTH, window_height / 3.0f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, GUI_HEIGHT), ImGuiCond_Always);
	ImGui::Begin("ShaderParam");
	m_LightingList[m_CurrentSelectShaderId]->DrawGUI();
	ImGui::End();
}
