#pragma once
#include "../Base/Base.h"

class ClearCollision : public Base
{
public:
	//各状態名
	enum
	{
		eState_NoHit,	//判定前
		eState_Hit,		//判定中
		eState_End,		//判定終了
	};

	//状態の変数
	int m_State;

	void NoHit();
	void Hit();
	void End();

public:
	struct Hit
	{
		static bool m_CollisionHit;
	};

	struct Switch
	{
		static bool m_CameraSwitch;
	};

public:
	ClearCollision(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};

class EnemyCollision : public Base
{
public:
	//各状態名
	enum
	{
		eState_NoHit,	//判定前
		eState_Hit,		//判定中
		eState_End,		//判定終了
	};

	//状態の変数
	int m_State;

	void NoHit();
	void Hit();
	void End();

public:
	int m_Count;

	struct Hit
	{
		static bool m_CollisionHit;
	};

	struct Switch
	{
		static bool m_EnemySwitch;
	};

public:
	EnemyCollision(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};

class BossCollision : public Base
{
public:
	//各状態名
	enum
	{
		eState_NoHit,	//判定前
		eState_Hit,		//判定中
		eState_End,		//判定終了
	};

	//状態の変数
	int m_State;

	void NoHit();
	void Hit();
	void End();

public:
	int m_Count;

	struct Hit
	{
		static bool m_CollisionHit;
	};

	struct Switch
	{
		static bool m_BossSwitch;
	};

public:
	BossCollision(const CVector3D& Pos);
	void Update();
	void Render();
	void Collision(Base* B);
};

