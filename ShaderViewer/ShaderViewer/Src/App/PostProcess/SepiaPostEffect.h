#ifndef SEPIA_POST_EFFECT_H_
#define SEPIA_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"

/**
* @brief �Z�s�A�������s���N���X
*/
class SepiaPostEffect : public PostEffectBase
{
private:
	/**
	* @brief �Z�s�A�p�����[�^�\����
	*/
	struct SepiaBuffer
	{
		float SpiaRate;		//! �Z�s�A��
		float Pad[3];		//! �T�C�Y��16�̔{���ɍ��킹�邽�߂̃p�f�B���O

		SepiaBuffer()
		{
			ZeroMemory(this, sizeof(SepiaBuffer));
		}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	SepiaPostEffect(VertexShader* vs_, PixelShader* ps_) :
		PostEffectBase(vs_, ps_)
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~SepiaPostEffect()
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
	SepiaBuffer			 m_SepiaBuffer;		//! �Z�s�A�p�����[�^�萔�o�b�t�@
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! �萔�o�b�t�@
};

#endif