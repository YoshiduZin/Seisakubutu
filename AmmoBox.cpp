#include "AmmoBox.h"

AmmoBox::AmmoBox(const CVector3D& Pos) : Base(eId_AmmoBox)
{
	m_Pos = Pos;
	m_AmmoBox = COPY_RESOURCE("AmmoBox", CModelObj);
	m_Rad = 1.0f;
}

void AmmoBox::Update()
{
	LineS = m_Pos;
	LineE = m_Pos;
}

void AmmoBox::Render()
{
	m_AmmoBox.SetPos(m_Pos + CVector3D(0, 0.5, 0));
	m_AmmoBox.SetScale(0.5, 0.5, 0.5);
	m_AmmoBox.Render();
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));

}

void AmmoBox::Collision(Base* B)
{

}