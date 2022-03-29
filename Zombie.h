#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Zombie : public Base
{
private:
	//各状態名
	enum
	{
		eState_Idle,		//通常状態
		eState_Mihakken,	//未発見状態
		eState_Hakken,		//発見状態
		eState_Attack1,		//攻撃状態(パターン1)
		eState_Attack2,		//攻撃状態(パターン2)
		eState_Damage,		//ダメージ状態
		eState_Down,		//死亡状態

	};

	//状態の変数
	int m_State;

	void Idle();
	void Mihakken();
	void Hakken();
	void UpdateTargetPoint();
	void Attack1();
	void Attack2();
	void Damage();
	void Down();

public:
	/* CModelA3M */
	//的モデルのオブジェクト
	CModelA3M m_Zombie;

	/* CMatrix */
	CMatrix View_Matrix;

	/* CVector3D */
	CVector3D LVec;
	CVector3D AVec;
	CVector3D View_Pos;
	CVector3D View_Dir;

	CVector3D Vec;
	CVector3D Vec_Z;

	CVector3D Target;
	bool	TargetIsPlyer;
	int		 TargetMoveTime;

	/* float , const float */
	float Length = 0;
	float Length_Z = 0;
	float View_Ang_Y;
	float View_Ang_X;
	float View_Length;
	float D = 0;
	float Ang;
	const float Move_Speed = 0.02f;
	const float Move_Speed2 = 0.1f;

	/* int */
	//体力
	int m_Hp;
	//削除関数
	int m_Delete;

	int m_Count1;
	int m_Count2;
	int m_Count3;

	/* bool */
	//攻撃
	bool m_Attack;
	bool m_Hakken = false;

public:
	//コンストラクタ
	Zombie(const CVector3D& Pos);
	~Zombie();
	//更新
	void Update();
	//描画
	void Render();
	//当たり判定の検証
	void Collision(Base* B);
};