#pragma once
#include "../Base/Base.h"

class UI : public Base
{
public:
	/* CImage */
	CImage m_Img[3];

public:
	UI();
	void Draw();
};