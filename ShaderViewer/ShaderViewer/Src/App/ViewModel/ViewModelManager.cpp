#include "ViewModelManager.h"
#include "../Config.h"
#include "../../Engine/Engine.h"
#include "../../Engine/imGui/imgui_impl_dx11.h"

void ViewModelManager::Update()
{
	if (!m_Model) return;
	
	m_Model.get()->Update();
}

void ViewModelManager::Draw()
{
	if (!m_Model) return;
	
	m_Model.get()->Draw();
}

void ViewModelManager::DrawGUI()
{
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(ConfigParameter::m_GuiWidth, ConfigParameter::m_GuiHeight), ImGuiCond_Always);
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
	// モデルの読み込み
	m_ObjModels.push_back(std::make_unique<ObjModel>());
	if (m_ObjModels[m_ObjModels.size() - 1].get()->Load(fileName)) {
		// 読み込みが成功したらリストに追加
		m_ModelsNameList.push_back(displayName_);
		m_Model.get()->SetModel(m_ObjModels[m_CurrentModelID].get());
		return true;
	}

	m_ObjModels.pop_back();
	return false;
}

