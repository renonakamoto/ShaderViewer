#ifndef LIGHTNG_MANAGER_H_
#define LIGHTNG_MANAGER_H_

#include <vector>
#include "LightingBase.h"


class LightingManager
{
public:
	LightingManager() :
		m_CurrentSelectShaderId(0)
	{}

	~LightingManager() {}

	static LightingManager* GetInstance()
	{
		static LightingManager instance;
		return &instance;
	}

	void Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_);

	/**
	* @fn void SetUpShader()
	* @brief 選択されているシェーダーをセットする関数
	*/
	void SetupShader() const;
	
	/**
	* @fn void DrawGUI()
	* @brief 選択されているシェーダーのGUI描画関数
	*/
	void DrawGUI();

private:
	int m_CurrentSelectShaderId;
	std::vector<const char*>   m_LightingNamesList;
	std::vector<std::unique_ptr<LightingBase>> m_LightingList;
};


#endif