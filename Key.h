#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Key1 : public Base
{
public:
	/* CModelObj */
	CModelObj m_Key1;

public:
	Key1(const CVector3D& Pos, const CVector3D& Rot);
	void Update();
	void Render();
	void Collision(Base* B);
};


class Key2 : public Base
{
public:
	/* CModelObj */
	CModelObj m_Key2;

public:
	Key2(const CVector3D& Pos, const CVector3D& Rot);
	void Update();
	void Render();
	void Collision(Base* B);
};