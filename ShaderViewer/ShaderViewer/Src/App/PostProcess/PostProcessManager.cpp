#include "PostProcessManager.h"
#include "../Definition.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void PostProcessManager::Entry(const char* displayName_, std::unique_ptr<PostEffectBase> postEffect_)
{
	if (!postEffect_) {
		return;
	}

	m_PostEffectNameList.push_back(displayName_);
	m_PostEffectList.push_back(std::move(postEffect_));
}

void PostProcessManager::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	m_PostEffectList[m_CurrentID]->Render(model_, bgModel_);
}

void PostProcessManager::DrawGUI()
{
	float window_width  = WINDOW->GetClientWidth();
	float window_height = WINDOW->GetClientHeight();
	
	float height = window_height / 3.0f * 2.0f;

	ImGui::SetNextWindowPos(ImVec2(0.0f, height), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, window_height), ImGuiCond_Always);
	ImGui::Begin("PostProcessList");
	ImGui::Separator();
	ImGui::Text("List1");
	ImGui::ListBox("", &m_CurrentID, m_PostEffectNameList.data(), static_cast<int>(m_PostEffectNameList.size()));
	ImGui::End();


	ImGui::SetNextWindowPos(ImVec2(window_width - GUI_WIDTH, height), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, GUI_HEIGHT), ImGuiCond_Always);
	ImGui::Begin("PostProcessParam");
	ImGui::Separator();
	m_PostEffectList[m_CurrentID]->DrawGUI();
	ImGui::End();
}