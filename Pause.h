#pragma once
#include "../Base/Base.h"

class Pause : public Base
{
private:
	//Šeó‘Ô–¼
	enum
	{
		eState_PauseEvent
	};

	//ó‘Ô‚Ì•Ï”
	int m_State;

	void PauseEvent();

public:
	/* CImage */
	CImage m_Img;
	int m_Count;

	struct Check
	{
		static bool PauseCheck;
		static bool SaveCheck;
	};

public:
	Pause();
	void Update();
	void Draw();
};