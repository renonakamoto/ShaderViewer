#include "MonochromePostEffect.h"
#include "../Lighting/LightingManager.h"
#include "../../Engine/Engine.h"

void MonochromePostEffect::Render(const ViewModel& model_, const ViewModel* bgModel_)
{
	// �����_�[�^�[�Q�b�g���I�t�X�N���[���ɐݒ�
	GRAPHICS->SetRenderTarget(KindRT::RT_OFF_SCREEN);

	// �V�F�[�_�[�̐ݒ�
	LightingManager::GetInstance()->SetupShader();

	// ���f���̕`��
	model_.Render();

	// �|�X�g�G�t�F�N�g
	GRAPHICS->SetRenderTarget(KindRT::RT_ON_SCREEN);
	m_ScreenSprite.Draw(DXVector3(0.0f, 0.0f, 0.0f));
}

void MonochromePostEffect::DrawGUI()
{
}
