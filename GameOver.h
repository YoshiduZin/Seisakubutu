#pragma once
#include "../Base/Base.h"

class GameOver : public Base
{
public:
	/* CImage */
	CImage m_Img;

public:
	GameOver();
	void Draw();
};