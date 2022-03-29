#pragma once
#include "../Base/Base.h"


class Title : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_StartEvent
	};

	//��Ԃ̕ϐ�
	int m_State;

	void StartEvent();

public:
	CImage m_Img[2];

	struct Screen
	{
		//�^�C�g��
		static bool m_Title;
		//�Q�[��
		static bool m_Game;
	};

	struct Switch
	{
		//�Z�[�u
		static bool m_SaveStart;
	};
public:
	Title();
	void Update();
	void Draw();
};