#ifndef PostEffectBase_H_
#define PostEffectBase_H_

#include "../ViewModel/ViewModel.h"
#include "../../Engine/Engine.h"
#include "../Object/Sprite/Sprite.h"


/**
* @brief �|�X�g�G�b�t�F�N�g�̊��N���X
*/
class PostEffectBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	PostEffectBase()
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~PostEffectBase()
	{}

	/**
	* @fn bool Init(VertexShader* vs_, PixelShader* ps_)
	* @brief �������֐�
	* @param[in] vs_ ���_�V�F�[�_�[
	* @param[in] ps_ �s�N�Z���V�F�[�_�[
	* @return bool �����������ǂ���
	*/
	bool Init(VertexShader* vs_, PixelShader* ps_);

	/**
	* @fn virtual void Render(const ViewModel& model_, const ViewModel* bgModel_) = 0
	* @brief �`��֐�
	* @param[in] model_ �r���[�p���f��
	* @param[in] bgModel_ �w�i�p���f��
	*/
	virtual void Render(const ViewModel& model_, const ViewModel* bgModel_) = 0;
	
	/**
	* @fn virtual void DrawGUI() = 0
	* @brief GUI�`��֐�
	*/
	virtual void DrawGUI() = 0;

protected:
	Sprite m_ScreenSprite;	//! �V�[���X�v���C�g

};

#endif