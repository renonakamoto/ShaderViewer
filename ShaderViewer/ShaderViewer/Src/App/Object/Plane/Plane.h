#ifndef PLANE_H_
#define PLANE_H_

#include "../../ViewModel/ViewModel.h"

/**
* @brief �v���[���I�u�W�F�N�g�N���X
*/
class Plane
{
public:
	Plane();

	~Plane()
	{}

	void Render();

	ViewModel* GetModel() { return &m_ViewModel; }

private:
	ViewModel m_ViewModel;
	ObjModel  m_Model;
};

#endif