#include "Plane.h"

Plane::Plane()
{
	m_Model.Load("Assets/Models/Plane.obj");
	m_ViewModel.SetModel(&m_Model);
	m_ViewModel.SetPos(DXVector3(0.0f, -2.0f, 0.0f));
	m_ViewModel.SetScale(DXVector3(0.05f, 0.05f, 0.05f));
}

void Plane::Draw()
{
	m_ViewModel.Draw();
}
