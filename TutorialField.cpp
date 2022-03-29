#include "TutorialField.h"
#include "../Screen/Title.h"

TutorialField::TutorialField() : Base(eId_TutorialField)
{
	m_Field = GET_RESOURCE("TutorialField", CModelObj);
	m_Field->SetScale(0.1f, 0.1f, 0.1f);
}

void TutorialField::Update()
{
}

void TutorialField::Render()
{
	if (Title::Screen::m_Title == false)
	{
		m_Field->Render();
	}
}

void TutorialField::Collision(Base* B)
{

}

TitleField::TitleField() : Base(eId_TitleField)
{
	m_Field = GET_RESOURCE("TitleField", CModelObj);
	m_Field->SetScale(0.1f, 0.1f, 0.1f);
}

void TitleField::Update()
{
}

void TitleField::Render()
{
	if (Title::Screen::m_Title == true)
	{
		m_Field->Render();
	}
}

void TitleField::Collision(Base* B)
{

}
