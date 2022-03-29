#include "EnemyKill.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

int EnemyKill::m_Score = 0;

EnemyKill::EnemyKill() : Base(eId_HUD)
{
	m_Img = COPY_RESOURCE("UI_Numbers",CImage);
}

void EnemyKill::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		for (int I = 0, S = m_Score; I < 2; I++, S /= 10)
		{
			int P = S % 10;
			m_Img.SetRect(0 + P * 110, 0, 110 + P * 110, 148);
			m_Img.SetPos(1835 - I * 30, 55);
			m_Img.SetSize(25, 48);
			m_Img.Draw();
		}
	}
}