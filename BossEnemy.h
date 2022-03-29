#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class BossEnemy : public Base
{
private:
	//各状態名
	enum
	{
		eState_Idle,	//通常状態
		eState_Mihakken,//未発見状態
		eState_Hakken,	//発見状態
		eState_Ikari,	//怒り状態
		eState_Attack1,	//弱攻撃状態
		eState_Attack2, //強攻撃状態
		eState_Attack3,	//ジャンプ攻撃状態
		eState_Damage,	//ダメージ状態
		eState_Down,	//死亡状態
	};

	//状態の変数
	int m_State;

	void Idle();
	void Mihakken();
	void Hakken();
	void Ikari();
	void Attack1();
	void Attack2();
	void Attack3();
	void Damage();
	void Down();

	int Point = 1;

public:
	/* CModelA3M */
	CModelA3M m_BossEnemy;

	/* CMatrix */
	CMatrix View_Matrix;

	/* CVector3D */
	//発見前の変数
	//距離のベクトル
	CVector3D LVec;
	//角度のベクトル
	CVector3D AVec;
	//目線の場所
	CVector3D View_Pos;
	//目線の角度
	CVector3D View_Dir;
	//発見後の変数
	CVector3D Vec;

	/* float , const float */
	//距離
	float Length = 0;
	//Y軸の角度
	float View_Ang_Y;
	//X軸の角度
	float View_Ang_X;
	//目線からの距離
	float View_Length;
	float D = 0;
	float Ang;
	//スピード管理
	
	//未発見時
	const float Move_Speed = 0.05f;
	//発見時
	const float Move_Speed2 = 0.1f;
	//怒り時
	const float Move_Speed3 = 0.15f;
	//ダッシュ
	const float Move_Speed4 = 0.2f;
	//ジャンプ(1パターン目)
	const float Move_Speed5 = 0.25f;
	//ジャンプ(2パターン目)
	const float Move_Speed6 = 0.35f;

	/* int */
	//体力
	int m_Hp;

	/* bool */
	//モード管理
	struct Mode
	{
		static bool m_Hakken;	//発見
		static bool m_Ikari;	//怒り
		static bool m_Jump;		//ジャンプ
	};

	bool m_Check;

	static const int Mode_Max = 3;

public:
	//コンストラクタ
	BossEnemy(const CVector3D& Pos);
	//更新
	void Update();
	//描画
	void Render();
	//当たり判定の検証
	void Collision(Base* B);
};