#ifndef ViewModelManager_H_
#define ViewModelManager_H_

#include <vector>
#include <memory>
#include "ViewModel.h"

/**
* @brief �r���[���f���̊Ǘ����s���N���X
*/
class ViewModelManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ViewModelManager():
		m_Model(nullptr),
		m_CurrentModelID(0)
	{
		m_Model = std::make_unique<ViewModel>();
	}
	
	/**
	* @brief �f�X�g���N�^
	*/
	~ViewModelManager()
	{}
	
	/**
	* @fn void Update()
	* @brief �X�V�֐�
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief �`��֐�
	*/
	void Render();

	/**
	* @fn void Update()
	* @brief GUI�`��֐�
	*/
	void DrawGUI();

	/**
	* @fn bool CreateModel(const char* fileName, const char* displayName_)
	* @brief ���f���쐬�֐�
	* @param[in] fileName	�@���f���f�[�^�̃t�@�C����(Obj�t�@�C��, �p�X�t��)
	* @param[in] displayName_ �f�B�X�v���C�ɕ\�������鎞�̖��O
	* @return bool �����������ǂ���
	* @details ���f���̓ǂݍ��݂ƃr���[���f���쐬���s��
	*/
	bool CreateModel(const char* fileName, const char* displayName_);

	/**
	* @fn ViewModel* GetModel()
	* @brief �I������Ă��郂�f���f�[�^���擾����֐�
	* @return ViewModel* �r���[���f���̃|�C���^
	*/
	ViewModel* GetModel() { return m_Model.get(); }

private:
	std::unique_ptr<ViewModel>				m_Model;			//! �r���[���f��
	std::vector<std::unique_ptr<ObjModel>>  m_ObjModels;		//! 3D���f���p
	std::vector<const char*>		        m_ModelsNameList;	//! ���f���̃f�B�X�v���C�����X�g
	int m_CurrentModelID;										//! ���ݑI������Ă郂�f����ID

};

#endif