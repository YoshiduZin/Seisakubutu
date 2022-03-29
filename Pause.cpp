#include "Pause.h"
#include <cstdlib>

bool Pause::Check::PauseCheck = false;

Pause::Pause() :Base(eId_Pause)
{
	m_Img = COPY_RESOURCE("Pause", CImage);
	m_State = eState_PauseEvent;
}

void Pause::Update()
{
	switch (m_State)
	{
	case eState_PauseEvent:
		PauseEvent();
		break;
	}
}

void  Pause::PauseEvent()
{
	
}

void Pause::Draw()
{
	if (Check::PauseCheck == true)
	{
		m_Img.Draw();
	}

}