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
			Shininess(0.f),
			Pad{20.f}
		{}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	BlinnPhong() :
		m_BlinnPhongBuffer{}
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
};

#endif