#ifndef SKY_DOME_H_
#define SKY_DOME_H_

#include "../../ViewModel/ViewModel.h"

class SkyDome
{
public:
	SkyDome();

	~SkyDome()
	{}

	void Render();

	ViewModel* GetModel() { return &m_ViewModel; }

private:
	ViewModel m_ViewModel;
	ObjModel  m_Model;
	
};

#endif