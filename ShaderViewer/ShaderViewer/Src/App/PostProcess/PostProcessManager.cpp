#include "PostProcessManager.h"
#include "../Config.h"
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

void PostProcessManager::Draw(const ViewModel& model_, const ViewModel* bgModel_)
{
	m_PostEffectList[m_CurrentID]->Draw(model_, bgModel_);
}

void PostProcessManager::DrawGUI()
{
	float window_width  = static_cast<float>(WINDOW->GetClientWidth());
	float window_height = static_cast<float>(WINDOW->GetClientHeight());
	
	float height = window_height / 3.0f * 2.0f;

	ImGui::SetNextWindowPos(ImVec2(0.0f, height), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, window_height), ImGuiCond_Always);
	ImGui::Begin("PostProcessList");
	ImGui::Separator();
	ImGui::Text("List1");
	ImGui::ListBox("", &m_CurrentID, m_PostEffectNameList.data(), static_cast<int>(m_PostEffectNameList.size()));
	ImGui::End();


	ImGui::SetNextWindowPos(ImVec2(window_width - ConfigParameter::m_GuiWidth, height), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, ConfigParameter::m_GuiHeight), ImGuiCond_Always);
	ImGui::Begin("PostProcessParam");
	ImGui::Separator();
	m_PostEffectList[m_CurrentID]->DrawGUI();
	ImGui::End();
}