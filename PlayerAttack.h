#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class PlayerAttack : public Base
{
public:
	/* CModelObj */
	CModelObj m_Bullet;

	/* CVector3D */
	CVector3D m_Dir;
	
	/* int */
	int Kill_Count;
public:
	PlayerAttack(const CVector3D& P,const CVector3D& D);
	void Update();
	void Render();
	void Collision(Base* B);
};