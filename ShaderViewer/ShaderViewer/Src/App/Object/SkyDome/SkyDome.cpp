#include "SkyDome.h"
#include "../../../Utility/Vector/DXVector.h"

SkyDome::SkyDome()
{
	m_Model.Load("Assets/Models/Skydome.obj");
	m_ViewModel.SetModel(&m_Model);
	m_ViewModel.SetPos(DXVector3(0.0f, -150.0f, -40.0f));
	m_ViewModel.SetScale(DXVector3(1.0f, 1.0f, 1.0f));
}

void SkyDome::Render()
{
	m_ViewModel.Render();
}
