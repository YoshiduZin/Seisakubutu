#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Arrow1 : public Base
{
public:
	/* CModelObj */
	CModelObj m_Arrow;

public:
	Arrow1(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};

class Arrow2 : public Base
{
public:
	/* CModelObj */
	CModelObj m_Arrow;

public:
	Arrow2(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};

