#include "Arrow.h"
#include "Player.h"
#include "Door.h"

Arrow1::Arrow1(const CVector3D& Pos) : Base(eId_Arrow)
{
	Base* D = Base::FindObject(eId_Door1);
	m_Pos = D->m_Pos + CVector3D(0,5,0.5);
	m_Arrow = COPY_RESOURCE("Arrow", CModelObj);
}

void Arrow1::Update()
{
}

void Arrow1::Render()
{
	Base* P = Base::FindObject(eId_Player);
	if (Door1::Switch::Door_1 == false && P->Key1_Count == 1)
	{
		CLight::SetLighting(false);
		m_Arrow.SetPos(m_Pos);
		m_Arrow.SetScale(0.5, 0.5, 0.5);
		m_Arrow.Render();
		CLight::SetLighting(true);
	}
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void Arrow1::Collision(Base* B)
{
}

Arrow2::Arrow2(const CVector3D& Pos) : Base(eId_Arrow)
{
	Base* D = Base::FindObject(eId_Door2);
	m_Pos = D->m_Pos + CVector3D(-0.5, 5, 0);
	m_Arrow = COPY_RESOURCE("Arrow", CModelObj);
}

void Arrow2::Update()
{
}

void Arrow2::Render()
{
	Base* P = Base::FindObject(eId_Player);
	if (Door2::Switch::Door_2 == false && P->Key2_Count == 1)
	{
		CLight::SetLighting(false);
		m_Arrow.SetPos(m_Pos);
		m_Arrow.SetScale(0.5, 0.5, 0.5);
		m_Arrow.Render();
		CLight::SetLighting(true);
	}
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void Arrow2::Collision(Base* B)
{
}