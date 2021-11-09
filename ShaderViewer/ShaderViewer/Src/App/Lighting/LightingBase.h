#ifndef LIGHTING_BASE_H_
#define LIGHTING_BASE_H_

#include <memory>
#include <wrl.h>
#include "../../Engine/Shader/VertexShader.h"
#include "../../Engine/Shader/PixelShader.h"

using namespace Microsoft::WRL;

/**
* @brief ���C�e�B���O���N���X
*/
class LightingBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	LightingBase():
		m_VertexShader(nullptr),
		m_PixelShader(nullptr)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~LightingBase()
	{}
	
	/**
	* @fn bool Init(VertexShader* vertexShader_, PixelShader* pixelShader_)
	* @brief �������֐�
	* @param[in] vertexShader_ ���_�V�F�[�_
	* @param[in] pixelShader_ �s�N�Z���V�F�[�_
	*/
	bool Init(VertexShader* vertexShader_, PixelShader* pixelShader_);
	
	/**
	* @fn void SetUpShader()
	* @brief �V�F�[�_�[�ݒ�֐�
	*/
	virtual void SetUpShader() const = 0;

	/**
	* @fn void DrawGUI()
	* @brief GUI�`��֐�
	*/
	virtual void DrawGUI() = 0;
	
protected:
	VertexShader*			  m_VertexShader;	//! ���_�V�F�[�_�[
	PixelShader*			  m_PixelShader;	//! �s�N�Z���V�F�[�_�[

};

#endif