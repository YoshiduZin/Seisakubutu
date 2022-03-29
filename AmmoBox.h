#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class AmmoBox : public Base
{
public:
	/* CModelObj */
	CModelObj m_AmmoBox;

public:
	AmmoBox(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};