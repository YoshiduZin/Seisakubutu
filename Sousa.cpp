#include "Sousa.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

Sousa::Sousa() : Base(eId_Sousa)
{
	m_Img = COPY_RESOURCE("Sousa", CImage);
}

void Sousa::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Img.SetPos(1650, 350);
		m_Img.SetSize(240, 400);
		m_Img.Draw();
	}
}
