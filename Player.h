#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"
#include "PlayerWepon.h"
#include "PlayerAttack.h"

class Player : public Base
{
private:
	//各状態名
	enum
	{
		eState_Idle,	//通常状態
		eState_Squat,	//しゃがみ状態
		eState_Prone,	//伏せ状態
		eState_Rotate,	//回転状態(伏せ限定)
		eState_Attack,	//攻撃状態
		eState_Damage,	//ダメージ状態
		eState_Down,	//死亡状態
		eState_Pause,	//ポーズ状態
		eState_Event	//イベント状態
	};

	//状態の変数
	int m_State;

	void Idle();
	void Squat();
	void Prone();
	void Rotate();
	void Attack();
	void Damage();
	void Down();
	void Menu();
	void Event();

public:
	/* CModelA3M */
	//モデルのオブジェクト
	CModelA3M m_Model;

	/* CMatrix */
	//プレイヤーの行列
	CMatrix Player_Matrix;
	//回転行列
	CMatrix Rot_Matrix;
	//プレイヤーの視点(ボーンに組み込み用)
	CMatrix View_Matrix;

	/* CVector3D */
	//入力方向ベクトル
	CVector3D Key_Dir;
	//プレイヤーの移動処理の関数
	CVector3D Dir;
	//射線
	CVector3D Wepon_Pos;
	CVector3D Vec;
	//視点系
	CVector3D LVec;
	CVector3D AVec;
	CVector3D View_Pos;
	CVector3D View_Dir;

	/* CVector2D */
	//マウスベクトル
	CVector2D Mouse_Vec;

	/* CImage */
	CImage m_Life[11];
	CImage m_Img[3];

	/* const float */
	//通常状態の移動量
	const float Move_Speed = 0.1f;
	//通常状態の移動量(武器を構える)
	const float Move_Speed2 = 0.045f;
	//しゃがみ状態の移動量
	const float Move_Speed3 = 0.045f;
	//しゃがみ状況の移動量(武器を構える)
	const float Move_Speed4 = 0.02f;
	//伏せ状態の移動量
	const float Move_Speed5 = 0.02f;
	//伏せ状態の移動量(左右に転がる)
	const float Move_Roll = 0.045f;
	/* float */
	//最大体力
	float m_Hp_Max;
	//現在の体力
	//float m_Hp_Now;
	float Length = 0;
	float D = 0;
	float View_Length;
	float View_Ang;
	float Ang;

	/* int */
	//リロード関数
	int m_Reload;
	//射撃関数
	int m_Shot;
	//銃の弾数
	int Bullet_Count;
	//銃弾の間隔
	int Bullet_Interval;
	//銃弾の補充
	int Bullet_Refill;
	//削除カウント
	int Kill_Count;

	int m_Count;

	int m_HitCount;

	struct Hyouzi
	{
		static bool m_Hyouzi1;
		static bool m_Hyouzi2;
		static bool m_Hyouzi3;
	};

	/* エリアの鍵 */
	struct GetKey
	{
		static bool m_Key1;
		static bool m_Key2;
	};
	static const int Key_Max = 2;
	
	/* 体制変化 */
	struct Mode
	{
		//しゃがみ
		static bool m_Squat;
		//伏せ
		static bool m_Prone;
	};

	struct Roll
	{
		//左	
		static bool m_RollLeft;
		//右
		static bool m_RollRight;
	};
	
	struct Switch
	{
		//ゲームクリア
		static bool m_GameClear;
		//ゲームオーバー
		static bool m_GameOver;
	};

	bool m_Button = false;

	struct Save
	{
		static bool m_Pause;
	};

	/* クラス使用 */
	//PlayerWeponクラスを使用
	PlayerWepon m_Wepon_Class;

public:
	
	//コンストラクタ
	Player(const CVector3D& Pos);
	~Player();
	//更新
	void Update();
	//描画
	void Render();
	//描画(体力用)
	void Draw();
	//当たり判定の検証
	void Collision(Base* B);
};
