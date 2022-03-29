#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class PlayerWepon : public Base
{
public:
	/* CModelObj */
	CModelObj m_PlayerWepon;	//アサルトライフル(Scar)
	
	/* CMatrix */
	CMatrix Player_Wepon_Matrix;	//アサルトライフル(Scar)
public:
	PlayerWepon();
	void Update();
	void Render();
};