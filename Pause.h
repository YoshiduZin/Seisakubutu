#pragma once
#include "../Base/Base.h"

class Pause : public Base
{
private:
	//各状態名
	enum
	{
		eState_PauseEvent
	};

	//状態の変数
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