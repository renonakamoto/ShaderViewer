#ifndef TOON_SHADING_H_
#define TOON_SHADING_H_

#include "LightingBase.h"

/**
* @brief ToonShader�N���X
*/
class ToonShading : public LightingBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	ToonShading();

	/**
	* @brief �f�X�g���N�^
	*/
	~ToonShading()
	{}

	/**
	* @fn void SetUpShader()
	* @brief �V�F�[�_�[�Z�b�g�֐�
	*/
	void SetUpShader() const override;

	/**
	* @fn void DrawGUI()
	* @brief �`��GUI�֐�
	*/
	void DrawGUI() override;

};

#endif