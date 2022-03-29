#include "UI.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

UI::UI() : Base(eId_HUD)
{
	m_Img[0] = COPY_RESOURCE("UI_Haikei", CImage);
	m_Img[1] = COPY_RESOURCE("UI_Haikei", CImage);
	m_Img[2] = COPY_RESOURCE("UI_Haikei", CImage);
}

void UI::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Img[0].SetPos(1650, 825);
		m_Img[0].SetSize(230, 215);
		m_Img[0].Draw();

		m_Img[1].SetPos(1781, 40);
		m_Img[1].SetSize(100, 80);
		m_Img[1].Draw();
		
		m_Img[2].SetPos(1640, 335);
		m_Img[2].SetSize(240, 430);
		m_Img[2].Draw();
	
	}
}