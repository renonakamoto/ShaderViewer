#ifndef MONOCHROME_POST_EFFECT_H_
#define MONOCHROME_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief ���m�N���������s���N���X
*/
class MonochromePostEffect : public PostEffectBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	MonochromePostEffect()
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~MonochromePostEffect()
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

};


#endif