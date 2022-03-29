#pragma once
#include "../Base/Base.h"

class Icon : public Base
{
public:
	/* CImage */
	CImage m_Img;

public:
	Icon();
	void Draw();
};