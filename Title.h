#pragma once
#include "../Base/Base.h"


class Title : public Base
{
private:
	//各状態名
	enum
	{
		eState_StartEvent
	};

	//状態の変数
	int m_State;

	void StartEvent();

public:
	CImage m_Img[2];

	struct Screen
	{
		//タイトル
		static bool m_Title;
		//ゲーム
		static bool m_Game;
	};

	struct Switch
	{
		//セーブ
		static bool m_SaveStart;
	};
public:
	Title();
	void Update();
	void Draw();
};