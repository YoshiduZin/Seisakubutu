#pragma once
#include "../Base/Base.h"

class RemainingBullets : public Base
{
public:
	/* CImage */
	CImage m_Img;

	/* int  */
	//�c�e��
	static int m_Remaining;

public:
	RemainingBullets();

	void Draw();
};