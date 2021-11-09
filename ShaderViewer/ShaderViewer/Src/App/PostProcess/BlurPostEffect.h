#ifndef BLUR_POST_EFFECT_H_
#define BLUR_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief �u���[�������s���N���X
*/
class BlurPostEffect : public PostEffectBase
{
private:
	/**
	* @brief �u���[�p�����[�^�p�\����
	*/
	struct BlurBuffer
	{
		float BlurStrength;	//! �u���[�̋���
		float Pad[3];		//! �T�C�Y��16�̔{���ɍ��킹�邽�߂̃p�f�B���O

		/**
		* @brief �R���X�g���N�^
		*/
		BlurBuffer()
		{
			ZeroMemory(this, sizeof(BlurBuffer));
		}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	BlurPostEffect()
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~BlurPostEffect()
	{}

	/**
	* @fn void Render(const ViewModel& model_, const ViewModel* bgModel_)
	* @brief �`��֐�
	* @param[in] model_ �r���[�p���f��
	* @param[in] bgModel_ �w�i�p���f��
	*/
	void Render(const ViewModel& model_, const ViewModel* bgModel_) override;

	/**
	* @fn void DrawGUI()
	* @brief GUI�`��֐�
	*/
	void DrawGUI() override;

private:
	/**
	* @fn bool CreateConstantBuffer()
	* @brief �萔�o�b�t�@�쐬�֐�
	* @return bool �����������ǂ���
	*/
	bool CreateConstantBuffer();

private:
	BlurBuffer			 m_BlurBuffer;		//! �u���[�p�����[�^�̒萔�o�b�t�@
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! �萔�o�b�t�@
};

#endif