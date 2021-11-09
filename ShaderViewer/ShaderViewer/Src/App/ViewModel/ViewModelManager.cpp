#include "ViewModelManager.h"
#include "../Definition.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void ViewModelManager::Update()
{
	if (!m_Model) return;
	
	m_Model.get()->Update();
}

void ViewModelManager::Render()
{
	if (!m_Model) return;
	
	m_Model.get()->Render();
}

void ViewModelManager::DrawGUI()
{
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(GUI_WIDTH, GUI_HEIGHT), ImGuiCond_Always);
	ImGui::Begin("ModelList");
	ImGui::Separator();
	ImGui::Text("List");
	if (ImGui::ListBox("", &m_CurrentModelID, m_ModelsNameList.data(), static_cast<int>(m_ModelsNameList.size()))) {
		m_Model.get()->SetModel(m_ObjModels[m_CurrentModelID].get());
	}
	ImGui::End();

	if (m_Model)
	{
		m_Model.get()->DrawGUI();
	}
}

bool ViewModelManager::CreateModel(const char* fileName, const char* displayName_)
{
	// ÉÇÉfÉãÇÃì«Ç›çûÇ›
	m_ObjModels.push_back(std::make_unique<ObjModel>());
	if (m_ObjModels[m_ObjModels.size() - 1].get()->Load(fileName)) {
		// ì«Ç›çûÇ›Ç™ê¨å˜ÇµÇΩÇÁÉäÉXÉgÇ…í«â¡
		m_ModelsNameList.push_back(displayName_);
		m_Model.get()->SetModel(m_ObjModels[m_CurrentModelID].get());
		return true;
	}

	m_ObjModels.pop_back();
	return false;
}

