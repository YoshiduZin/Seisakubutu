#include "Title.h"
#include "../Game/Player.h"
#include "../Game/HitCollision.h"
#include "../Game/Zombie.h"
#include "../Data/SaveData/Save.h"
#include "../Game/EnemyKill.h"
#include "../Game/Key.h"
#include "../Game/Door.h"

bool Title::Screen::m_Title = true;
bool Title::Switch::m_SaveStart = false;

Title::Title() : Base(eId_Title)
{
	m_Img[0] = COPY_RESOURCE("Title", CImage);
	m_Img[1] = COPY_RESOURCE("Sentaku", CImage);

	Count = 0;
	m_State = eState_StartEvent;
	Screen::m_Title = true;
}

void Title::Update()
{
	switch (m_State)
	{
	case eState_StartEvent:
		StartEvent();
		break;
	}
}

void Title::StartEvent()
{
	if (CInput::GetState(0, CInput::ePush, CInput::eUp))
	{
		//メニュー選択カウントが１以上の時
		if (Count > 0)
		{
			//メニュー選択カウントを減らす
			Count--;
		}
		else
		{
			//メニュー選択カウントを2にする
			Count = 1;
		}
	}

	if (CInput::GetState(0, CInput::ePush, CInput::eDown))
	{
		//メニュー選択カウントが１以上の時
		if (Count < 1)
		{
			//メニュー選択カウントを減らす
			Count++;
		}
		else
		{
			//メニュー選択カウントを2にする
			Count = 0;
		}
	}

	if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Screen::m_Title == true && Count == 0)
	{
		Switch::m_SaveStart = false;
		Screen::m_Title = false;
	}

	if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Screen::m_Title == true && Count == 1)
	{
		Switch::m_SaveStart = true;
		Save::Reading();
		Screen::m_Title = false;
	
		Base* P = Base::FindObject(eId_Player);
		if (P->Key1_Count == 1)
		{
			Door1::Switch::Door_1 = true;
		}
	}
}

void Title::Draw()
{
	if (Screen::m_Title == true)
	{
		m_Img[0].Draw();

		m_Img[1].SetPos(CVector2D(655, 670 + 200 * Count));
		m_Img[1].Draw();
	}
}