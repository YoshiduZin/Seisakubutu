#include "Icon.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

Icon::Icon() : Base(eId_HUD)
{
	m_Img = COPY_RESOURCE("UI_Icon1", CImage);
}

void Icon::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Img.SetPos(1690, 885);
		m_Img.SetSize(150, 100);
		m_Img.Draw();
	}
}
