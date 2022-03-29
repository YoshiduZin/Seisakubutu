#pragma once
#include "../Base/Base.h"

class GameClear : public Base
{
private:
	//各状態名
	enum
	{
		eState_Event
	};

	//状態の変数
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