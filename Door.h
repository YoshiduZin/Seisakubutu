#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Door1 : public Base
{
private:
	//各状態名
	enum
	{
		eState_Idle,	//触れる前のドア
		eState_Open,	//ドアが開く
		eState_Close,	//ドアが閉じる
	};

	//状態の変数
	int m_State;

	void Idle();
	void Open();
	void Close();

public:
	/* CModelObj */
	CModelObj m_Door1;
	struct Mode
	{
		static bool m_OpenDoor1;
	};

	struct Switch
	{
		static bool Door_1;
	};

public:
	Door1(const CVector3D& Pos, const CVector3D& Rot);
	void Update();
	void Render();
	void Collision(Base* B);
};

class Door2 : public Base
{
private:
	//各状態名
	enum
	{
		eState_Idle,	//触れる前のドア
		eState_Open,	//ドアが開く
		eState_Close,	//ドアが閉じる
	};

	//状態の変数
	int m_State;

	void Idle();
	void Open();
	void Close();

public:
	/* CModelObj */
	CModelObj m_Door2;
	struct Mode
	{
		static bool m_OpenDoor2;
	};

	struct Switch
	{
		static bool Door_2;
	};

public:
	Door2(const CVector3D& Pos, const CVector3D& Rot);
	void Update();
	void Render();
	void Collision(Base* B);
};