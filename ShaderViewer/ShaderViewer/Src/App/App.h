#ifndef APP_H_
#define APP_H_

#include "Camera/Camera.h"
#include "ViewModel/ViewModelManager.h"
#include "Lighting/LightingManager.h"
#include "PostProcess/NormalPostEffect.h"
#include "PostProcess/BlurPostEffect.h"
#include "PostProcess/PostProcessManager.h"
#include "Object/SkyDome/SkyDome.h"
#include "Object/Plane/Plane.h"

/**
* @brief �A�v���̐���N���X
*/
class App
{
public:
	/**
	* @fn static App* GetInstance()
	* @brief �C���X�^���X��Ԃ��֐�
	* @return App* �C���X�^���X�̃|�C���^
	*/
	static App* GetInstance()
	{
		static App instance;
		return &instance;
	}

	/**
	* @fn bool Init()
	* @brief �A�v���P�[�V�����̏��������s���֐�
	* @return bool �����������ǂ���
	*/
	bool Init();

	/**
	* @fn void Run()
	* @brief ���s�֐�
	* @details �A�v���P�[�V�����̍X�V�ƕ`����s��
	*/
	void Run();

private:
	/**
	* @fn void Update()
	* @brief �A�v���P�[�V�����̍X�V���s���֐�
	*/
	void Update();

	/**
	* @fn void Render()
	* @brief �A�v���P�[�V�����̕`����s���֐�
	*/
	void Render();

	/**
	* @fn void SetUpDepthShader()
	* @brief �V���h�E�}�b�v�̐ݒ���s���֐�
	*/
	void SetUpDepthShader();

	/**
	* @fn void SetUpUnlitShader()
	* @brief �A�����b�g�`��ݒ���s���֐�
	*/
	void SetUpUnlitShader();

	/**
	* @fn void DrawDepth()
	* @brief �V���h�E�}�b�v�̕`����s���֐�
	*/
	void DrawDepth();

private:
	/**
	* @fn bool InitModels()
	* @brief ���f���̏������֐�
	* @return bool �����������ǂ���
	*/
	bool InitModels();

	/**
	* @fn bool InitShader()
	* @brief �V�F�[�_�[�̏������֐�
	* @return bool �����������ǂ���
	*/
	bool InitShaders();

	/**
	* @fn bool InitLigtings()
	* @brief ���C�e�B���O�̏������֐�
	* @return bool �����������ǂ���
	*/
	bool InitLigtings();

	/**
	* @fn bool InitPostProcess()
	* @brief �|�X�g�v���Z�X�̏������֐�
	*/
	void InitPostProcess();

private:
	/**
	* @brief �R���X�g���N�^
	*/
	App()
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~App()
	{}

private:
	std::unique_ptr<Camera>	 m_Camera;				//! �J����
	ViewModelManager		 m_ModelManager;		//! ���f���}�l�[�W��	
	PostProcessManager		 m_PostProcessManager;	//! �|�X�g�v���Z�X�}�l�[�W��

	// �w�i�I�u�W�F�N�g
	SkyDome m_SkyDome;	//! �X�J�C�h�[��
	Plane   m_Plane;	//! �v���[��
};

#define APP App::GetInstance()

#endif