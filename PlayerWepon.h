#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class PlayerWepon : public Base
{
public:
	/* CModelObj */
	CModelObj m_PlayerWepon;	//�A�T���g���C�t��(Scar)
	
	/* CMatrix */
	CMatrix Player_Wepon_Matrix;	//�A�T���g���C�t��(Scar)
public:
	PlayerWepon();
	void Update();
	void Render();
};