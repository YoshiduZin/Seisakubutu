#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class TutorialField : public Base
{
public:
	/*CModelObj*/
	CModelObj* m_Field;
public:
	TutorialField();
	void Update();
	void Render();
	void Collision(Base* B);
	CModel* GetModel()
	{
		return m_Field;
	}
};

class TitleField : public Base
{
public:
	/*CModelObj*/
	CModelObj* m_Field;
public:
	TitleField();
	void Update();
	void Render();
	void Collision(Base* B);
	CModel* GetModel()
	{
		return m_Field;
	}
};