#pragma once
#include "../Base/Base.h"

class GameClear : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_Event
	};

	//��Ԃ̕ϐ�
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