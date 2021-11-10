#ifndef BLINN_PHONG_H_
#define BLINN_PHONG_H_

#include "LightingBase.h"

/**
* @brief BlinnPhong�V�F�[�f�B���O�N���X
*/
class BlinnPhong : public LightingBase
{
private:
	/**
	* @brief BlinnPhong�p�\����
	*/
	struct BlinnPhongBuffer
	{
		float Shininess;	//! �n�C���C�g�̋���(�Ⴂ�قǋ�������)
		float Pad[3];		//! �T�C�Y��16�̔{���ɍ��킹�邽�߂̃p�f�B���O
		
		/**
		* @brief �R���X�g���N�^
		*/
		BlinnPhongBuffer():
			Shininess(20.f),
			Pad{20.f}
		{}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	BlinnPhong() :
		m_BlinnPhongBuffer{},
		m_MinShiness(5.0f),
		m_MaxShiness(200.0f)
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~BlinnPhong()
	{}

	/**
	* @fn void SetUpShader()
	* @brief �V�F�[�_�[�Z�b�g�֐�
	*/
	void SetUpShader() const override;

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
	BlinnPhongBuffer	 m_BlinnPhongBuffer;	//! BlinnPhong�p�\���̕ϐ�
	ComPtr<ID3D11Buffer> m_ConstantBuffer;		//! �R���X�g�o�b�t�@
	const float			 m_MinShiness;			//! �n�C���C�g�̋����̍ŏ��l
	const float			 m_MaxShiness;			//! �n�C���C�g�̋����̍ő�l
};

#endif