#include "GameOver.h"

GameOver::GameOver() :Base(eId_Screen)
{
	m_Img = COPY_RESOURCE("GameOver", CImage);
}

void GameOver::Draw()
{
	m_Img.Draw();
}