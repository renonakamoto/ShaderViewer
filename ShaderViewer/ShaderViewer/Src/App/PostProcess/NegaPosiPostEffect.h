#ifndef NEGAPOSI_POST_EFFECT_H_
#define NEGAPOSI_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief �l�K�|�W���]�������s���N���X
*/
class NegaPosiPostEffect : public PostEffectBase
{
private:
	/**
	* @brief �l�K�|�W�p�����[�^�\����
	*/
	struct NegaBuffer
	{
		float NegaRate;		//! �l�K�|�W���]��
		float Pad[3];		//! �T�C�Y��16�̔{���ɍ��킹�邽�߂̃p�f�B���O

		/**
		* @brief �l�K�|�W�p�����[�^�\����
		*/
		NegaBuffer()
		{
			ZeroMemory(this, sizeof(NegaBuffer));
		}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	NegaPosiPostEffect()
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~NegaPosiPostEffect()
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
	NegaBuffer			 m_NegaBuffer;		//! �l�K�|�W�p�\���̕ϐ�
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! �R���X�g�o�b�t�@
};

#endif