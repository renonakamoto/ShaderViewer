#ifndef OUTLINE_POST_EFFECT_H_
#define OUTLINE_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief �A�E�g���C���������s���N���X
*/
class OutlinePostEffect : public PostEffectBase
{
private:
	/**
	* @brief �A�E�g���C���p�����[�^�\����
	*/
	struct OutlineBuffer
	{
		float Color[3];
		float Pad;

		OutlineBuffer()
		{
			ZeroMemory(this, sizeof(OutlineBuffer));
		}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	OutlinePostEffect(VertexShader* vs_, PixelShader* ps_) :
		PostEffectBase(vs_, ps_)
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~OutlinePostEffect()
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
	OutlineBuffer		 m_OutlineBuffer;
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! �R���X�g�o�b�t�@

};

#endif