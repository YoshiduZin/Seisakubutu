#include "Shikiri.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

Shikiri::Shikiri() : Base(eId_HUD)
{
	m_Img = COPY_RESOURCE("UI_Shikiri", CImage);
}

void Shikiri::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Img.SetPos(1730, 960);
		m_Img.SetSize(55, 70);
		m_Img.Draw();
	}
}