#ifndef LIGHTNG_MANAGER_H_
#define LIGHTNG_MANAGER_H_

#include <vector>
#include "LightingBase.h"

/**
* @brief Lighing�I�u�W�F�N�g�Ǘ��N���X
*/
class LightingManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	LightingManager() :
		m_CurrentSelectShaderId(0)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~LightingManager() {}

	/**
	* @fn static LightingManager* GetInstance()
	* @brief �C���X�^���X��Ԃ��֐�
	* @return LightingManager* �C���X�^���X�̃|�C���^
	*/
	static LightingManager* GetInstance()
	{
		static LightingManager instance;
		return &instance;
	}

	/**
	* @fn void Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_)
	* @brief Lighting�I�u�W�F�N�g�̓o�^�֐�
	* @param[in] displayName_ �f�B�X�v���C�ɕ\�������閼�O
	* @param[in] lig_ Lighting�I�u�W�F�N�g
	*/
	void Entry(const char* displayName_, std::unique_ptr<LightingBase> lig_);

	/**
	* @fn void SetUpShader()
	* @brief �I������Ă���V�F�[�_�[���Z�b�g����֐�
	*/
	void SetupShader() const;
	
	/**
	* @fn void DrawGUI()
	* @brief �I������Ă���V�F�[�_�[��GUI�`��֐�
	*/
	void DrawGUI();

private:
	int m_CurrentSelectShaderId;								//! ���ݑI������Ă���V�F�[�_�[ID
	std::vector<const char*>   m_LightingNamesList;				//! ���C�e�B���O�����X�g
	std::vector<std::unique_ptr<LightingBase>> m_LightingList;	//! ���C�e�B���O���X�g
};


#endif