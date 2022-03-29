#pragma once
#include "../Base/Base.h"

class EnemyKill : public Base
{
public:
	/* CImage */
	CImage m_Img;

	/* int */
	//“¢”°”
	static int m_Score;

public:
	EnemyKill();
	void Draw();
};