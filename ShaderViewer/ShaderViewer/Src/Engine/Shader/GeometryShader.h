#ifndef GEOMETRY_SHADER_H_
#define GEOMETRY_SHADER_H_

#include <d3d11.h>
#include <wrl.h>
#include "ShaderBase.h"


/**
* @brief �W�I���g���[�V�F�[�_�����N���X
*/
class GeometryShader : public ShaderBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	GeometryShader() :
		m_Interface(nullptr)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~GeometryShader() final
	{}

	/**
	* @fn bool Create(ID3D11Device* device_, const char* fileName_))
	* @brief �W�I���g���[�V�F�[�_�[�̍쐬���s���֐�
	* @param[in] device_ �f�o�C�X
	* @param[in] fileName_ �t�@�C����(�p�X�t)
	* @return bool �����������ǂ�����^�U�ŕԂ�
	* @details ���łɃR���p�C������Ă���cso�t�@�C�����w�肷��
	*/
	bool Create(ID3D11Device* device_, const char* fileName_)override;

	/**
	* @fn ID3D11VertexShader* GetShaderInterface()
	* @brief �V�F�[�_�[�̃C���^�[�t�F�[�X��Ԃ��֐�
	* @return ID3D11VertexShader* �C���^�[�t�F�[�X�̃|�C���^
	*/
	ID3D11GeometryShader* GetShaderInterface()
	{
		return m_Interface.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> m_Interface;	//! �s�N�Z���V�F�[�_�[�C���^�[�t�F�[�X
};

#endif