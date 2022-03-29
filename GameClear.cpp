#include "GameClear.h"
#include "../Game/Player.h"

GameClear::GameClear() :Base(eId_Screen)
{
	m_Img = COPY_RESOURCE("GameClear", CImage);

	m_State = eState_Event;
}

void GameClear::Update()
{
	switch (m_State)
	{
	case eState_Event:
		Event();
		break;
	}
	
}

void GameClear::Event()
{
	
	if (Player::Switch::m_GameClear == true)
	{
		if (m_Count < 300)
		{
			m_Pos += CVector2D(0, 1);
			m_Count++;
		}
	}
}

void GameClear::Draw()
{
	if (Player::Switch::m_GameClear == true)
	{
		m_Img.SetPos(500,m_Pos.y);
		m_Img.Draw();
	}

}