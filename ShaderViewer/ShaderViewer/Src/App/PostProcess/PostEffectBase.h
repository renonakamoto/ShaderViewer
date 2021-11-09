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
	PostEffectBase(VertexShader* vs_, PixelShader* ps_)
	{
		m_ScreenSprite.Init(
			GRAPHICS->GetRenderTarget(KindRT::RT_OFF_SCREEN)->GetTexture(),
			WINDOW->GetClientWidth(),
			WINDOW->GetClientHeight(),
			vs_,
			ps_
		);
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~PostEffectBase()
	{}

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