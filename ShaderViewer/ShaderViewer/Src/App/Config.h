#ifndef CONFIG_H_
#define CONFIG_H_

#include "../Utility/Vector/DXVector.h"

/**
* @brief �ݒ�p�����[�^��ێ�����N���X
*/
class ConfigParameter
{
public:
	/**
	* @fn void Load()
	* @brief Config�f�[�^�̓ǂݍ��݊֐�
	*/
	static void Load();

public:
	static float m_CameraFov;	//! �J��������
	static float m_CameraNear;	//! �J����near
	static float m_CameraFar;	//! �J����far

	static float m_GuiWidth;	//! GUI�̉���
	static float m_GuiHeight;	//! GUI�̏c��

	static DXVector3 m_LightPos;//! ���C�g�̍��W
};

#endif