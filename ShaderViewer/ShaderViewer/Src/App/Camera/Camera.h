#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../Utility/Vector/DXVector.h"

/**
* @brief �����_�[�^�[�Q�b�g�̎��
*/
class Camera
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	Camera() :
		Camera({ 0.f, 2.f, -12.f }, { 0.f, 0.f, 0.f }, { 0.f, 1.f, 0.f })
	{}

	/**
	* @brief �R���X�g���N�^
	*/
	Camera(DXVector3 pos_, DXVector3 forcus_, DXVector3 up_) :
		m_Pos(pos_),
		m_FocusPos(forcus_),
		m_Up(up_)
	{}

	/**
	* @brief �f�X�g���N�^
	*/
	~Camera() {}

	/**
	* @fn void Update()
	* @brief �X�V�֐�
	* @details View�s��Projection�s��̍쐬���s���萔�o�b�t�@�ɐݒ肷��
	*/
	void Update();

private:
	DXVector3 m_Pos;		//! ���W
	DXVector3 m_FocusPos;	//! �����_
	DXVector3 m_Up;			//! ������x�N�g��

};

#endif