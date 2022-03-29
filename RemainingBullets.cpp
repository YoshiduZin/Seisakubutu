#include "RemainingBullets.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

int RemainingBullets::m_Remaining = 300;
//int RemainingBullets::m_Remaining = 999;

RemainingBullets::RemainingBullets() : Base(eId_HUD)
{
	m_Img = COPY_RESOURCE("UI_Numbers", CImage);
}

void RemainingBullets::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		for (int I = 0, S = m_Remaining; I < 3; I++, S /= 10)
		{
			int P = S % 10;
			m_Img.SetRect(0 + P * 110, 0, 110 + P * 110, 148);
			m_Img.SetPos(1840 - I * 30, 970);
			m_Img.SetSize(25, 48);
			m_Img.Draw();
		}
	}	
}