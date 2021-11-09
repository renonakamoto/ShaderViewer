#ifndef NORMAL_POST_EFFECT_H_
#define NORMAL_POST_EFFECT_H_

#include "PostEffectBase.h"
#include "../Object/Sprite/Sprite.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Shader/ShaderManager.h"

/**
* @brief �ʏ�`�揈�����s���N���X
*/
class NormalPostEffect : public PostEffectBase
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	NormalPostEffect(VertexShader* vs_, PixelShader* ps_) :
		PostEffectBase(vs_, ps_)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~NormalPostEffect()
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