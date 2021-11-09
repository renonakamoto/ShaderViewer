#ifndef POST_PROCESS_MANAGERE_H_
#define POST_PROCESS_MANAGERE_H_

#include "../ViewModel/ViewModel.h"
#include "PostEffectBase.h"

/**
* @brief �|�X�g�v���Z�X�̊Ǘ����s���N���X
*/
class PostProcessManager
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	PostProcessManager():
		m_CurrentID(0)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~PostProcessManager()
	{}
	
	/**
	* @fn void Entry(const char* displayName_, std::unique_ptr<PostEffectBase> postEffect_)
	* @brief �|�X�g�G�t�F�N�g�I�u�W�F�N�g�̓o�^�֐�
	* @param[in] displayName_ �f�B�X�v���C�ɕ\�������閼�O
	* @param[in] postEffect_ �|�X�g�G�t�F�N�g�I�u�W�F�N�g
	*/
	void Entry(const char* displayName_, std::unique_ptr<PostEffectBase> postEffect_);

	/**
	* @fn void Render(const ViewModel& model_, const ViewModel* bgModel_)
	* @brief �`��֐�
	* @param[in] model_ �r���[�p���f��
	* @param[in] bgModel_ �w�i�p���f��
	*/
	void Render(const ViewModel& model_, const ViewModel* bgModel_);
	
	/**
	* @fn void DrawGUI()
	* @brief GUI�`��֐�
	*/
	void DrawGUI();

private:
	std::vector<std::unique_ptr<PostEffectBase>> m_PostEffectList;		//! �|�X�g�G�t�F�N�g���X�g
	std::vector<const char*>					 m_PostEffectNameList;	//! �|�X�g�G�t�F�N�g�����X�g
	int											 m_CurrentID;			//! ���݂�ID
};

#endif