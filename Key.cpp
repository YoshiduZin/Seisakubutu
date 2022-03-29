#include "Key.h"

Key1::Key1(const CVector3D& Pos, const CVector3D& Rot) : Base(eId_Key1)
{
	m_Pos = Pos;
	m_Rot = Rot;
	m_Key1 = COPY_RESOURCE("Key1", CModelObj);
	m_Rad = 0.3f;

}

void Key1::Update()
{
	m_Rot.y -= DtoR(5);
	LineS = m_Pos + CVector3D(0, -0.4, 0);
	LineE = m_Pos + CVector3D(0, 0.6, 0);
}

void Key1::Render()
{
	m_Key1.SetPos(m_Pos);
	m_Key1.SetRot(m_Rot);
	m_Key1.SetScale(0.01f, 0.01f, 0.01f);
	m_Key1.Render();
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void Key1::Collision(Base* B)
{
}


Key2::Key2(const CVector3D& Pos, const CVector3D& Rot) : Base(eId_Key2)
{
	m_Pos = Pos;
	m_Rot = Rot;
	m_Key2 = COPY_RESOURCE("Key2", CModelObj);
	m_Rad = 0.3f;

}

void Key2::Update()
{
	m_Rot.y -= DtoR(5);
	LineS = m_Pos + CVector3D(0, -0.4, 0);
	LineE = m_Pos + CVector3D(0, 0.6, 0);
}

void Key2::Render()
{
	m_Key2.SetPos(m_Pos);
	m_Key2.SetRot(m_Rot);
	m_Key2.SetScale(0.01f, 0.01f, 0.01f);
	m_Key2.Render();
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void Key2::Collision(Base* B)
{
}
