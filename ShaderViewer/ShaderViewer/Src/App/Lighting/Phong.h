#ifndef PHONG_H_
#define PHONG_H_

#include "LightingBase.h"

/**
* @brief PhongShading�N���X
*/
class Phong : public LightingBase
{
private:
	/**
	* @brief �t�H���p�����[�^�\����
	*/
	struct PhongBuffer
	{
		float Shininess;	//! �n�C���C�g�̋���(�Ⴂ�قǋ�������)
		float Pad[3];		//! �T�C�Y��16�̔{���ɍ��킹�邽�߂̃p�f�B���O

		/**
		* @brief �R���X�g���N�^
		*/
		PhongBuffer():
			Shininess(20.f),
			Pad{0.f}
		{}
	};

public:
	/**
	* @brief �R���X�g���N�^
	*/
	Phong() :
		m_PhongBuffer{}
	{
		CreateConstantBuffer();
	}

	/**
	* @brief �f�X�g���N�^
	*/
	~Phong()
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
	PhongBuffer			 m_PhongBuffer;		//! �t�H���p�\���̕ϐ�
	ComPtr<ID3D11Buffer> m_ConstantBuffer;	//! �R���X�g�o�b�t�@
};

#endif