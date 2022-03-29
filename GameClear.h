#pragma once
#include "../Base/Base.h"

class GameClear : public Base
{
private:
	//Šeó‘Ô–¼
	enum
	{
		eState_Event
	};

	//ó‘Ô‚Ì•Ï”
	int m_State;

	void Event();

public:
	/* CImage */
	CImage m_Img;
	int m_Count;

public:
	GameClear();
	void Update();
	void Draw();
};