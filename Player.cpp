#include "Player.h"
#include "BulletNumber.h"
#include "RemainingBullets.h"
#include "../Screen/GameOver.h"
#include "../Screen/GameClear.h"
#include "BossEnemy.h"
#include "Door.h"
#include "HitCollision.h"
#include "../Screen/Title.h"
#include "../Screen/Pause.h"
#include "SaveSpot.h"

/* 鍵の所得 */
bool Player::GetKey::m_Key1 = false;
bool Player::GetKey::m_Key2 = false;

/* プレイヤーのモード */
bool Player::Mode::m_Squat = false;
bool Player::Mode::m_Prone = false;

/* しゃがみ状態での左右の移動 */
bool Player::Roll::m_RollLeft = false;
bool Player::Roll::m_RollRight = false;

/* スイッチ切り替え */
bool Player::Switch::m_GameClear = false;
bool Player::Switch::m_GameOver = false;

/* 表示 */
bool Player::Hyouzi::m_Hyouzi1 = false;
bool Player::Hyouzi::m_Hyouzi2 = false;
bool Player::Hyouzi::m_Hyouzi3 = false;

/* セーブ */
bool Player::Save::m_Pause = false;

Player::Player(const CVector3D& P) : Base(eId_Player)
{
	m_Pos = P;
	m_Model = COPY_RESOURCE("Player", CModelA3M);
	m_Rad = 0.4f;

	m_Reload = false;
	m_Shot = false;

	Bullet_Interval = 0;

	m_HitCount = 0;

	if (Title::Switch::m_SaveStart == false)
	{
		//弾数(60発)
		Bullet_Count = 60;
		//最大体力
		m_Hp_Max = 100;
		//現在の体力
		m_Hp_Now = m_Hp_Max;
		Key1_Count = 0;
		Key2_Count = 0;
	}

	m_Hit_Id = 0;

	//体力の最大(3)
	//体力ゲージ
	m_Life[0] = COPY_RESOURCE("Hp10", CImage);
	m_Life[1] = COPY_RESOURCE("Hp9", CImage);
	m_Life[2] = COPY_RESOURCE("Hp8", CImage);
	m_Life[3] = COPY_RESOURCE("Hp7", CImage);
	m_Life[4] = COPY_RESOURCE("Hp6", CImage);
	m_Life[5] = COPY_RESOURCE("Hp5", CImage);
	m_Life[6] = COPY_RESOURCE("Hp4", CImage);
	m_Life[7] = COPY_RESOURCE("Hp3", CImage);
	m_Life[8] = COPY_RESOURCE("Hp2", CImage);
	m_Life[9] = COPY_RESOURCE("Hp1", CImage);
	m_Life[10] = COPY_RESOURCE("Hp0", CImage);

	//アイテム確認
	m_Img[0] = COPY_RESOURCE("SpaceKey", CImage);
	m_Img[1] = COPY_RESOURCE("Tama30", CImage);
	m_Img[2] = COPY_RESOURCE("Tama100", CImage);

	//はじめは通常状態へ
	if (Title::Screen::m_Title == false)
	{

		m_State = eState_Idle;
	}

	if (Title::Screen::m_Title == true)
	{
		m_State = eState_Event;
	}

	if (Title::Switch::m_SaveStart == true)
	{
		m_State = eState_Event;
	}

	//上半身(ボーンをまとめる)
	for (int I = 5; I <= 73; I++)
	{
		CA3MNode* node = m_Model.GetNode(I);
		node->SetAnimationLayer(1);
	}
}

Player::~Player()
{

}

void Player::Update()
{
	m_Pos_Old = m_Pos;
	//状態の切り替え
	switch (m_State)
	{
	case eState_Idle:
		Idle();		//通常状態へ
		break;
	case eState_Squat:
		Squat();	//しゃがみ状態へ
		break;
	case eState_Prone:
		Prone();	//伏せ状態へ
		break;
	case eState_Rotate:
	Rotate();	//回転状態(伏せ状態のみ)へ
		break;
	case eState_Attack:
		Attack();	//攻撃状態へ
		break;
	case eState_Damage:
		Damage();	//ダメージ状態
		break;
	case eState_Down:
		Down();	//死亡状態へ
		break;
	case eState_Pause:
		Menu();	//ポーズ状態へ
		break;
	case eState_Event:
		Event();
		break;
	}
	
	//モーションの更新
	m_Model.UpdateAnimation();

	if (Mode::m_Squat == false)
	{
		LineS = m_Pos + CVector3D(0, 0.6, 0);
		LineE = m_Pos + CVector3D(0, 1.3, 0);
	}

	else if (Mode::m_Squat == true)
	{
		LineS = m_Pos + CVector3D(0, 0.2, 0);
		LineE = m_Pos + CVector3D(0, 0.8, 0);
	}

	Center = m_Pos + CVector3D(0, 1, 0);
	m_Vec.y -= GRVITY;
	m_Pos += m_Vec;

}

void Player::Idle()
{
	//printf("実行中");
	if (Mode::m_Squat == true)
	{
		m_Model.ChangeAnimation(24);
		Mode::m_Squat = false;
		if (m_Model.isAnimationEnd())
		{
		}
	}

	if (Mode::m_Squat == false)
	{
		Key_Dir = CVector3D(0, 0, 0);

		//マウス操作でキャラクターを回転
		Mouse_Vec = CInput::GetMouseVec();
		m_Rot.y += Mouse_Vec.x * -0.002f;
		m_Rot.x += Mouse_Vec.y * 0.002f;
		m_Rot.x = min(DtoR(45), max(DtoR(-45), m_Rot.x));

		//方向キーから入力方向ベクトルを設定
		if (CInput::GetState(0, CInput::eHold, CInput::eUp))
		{
			Key_Dir.z = 1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eDown))
		{
			Key_Dir.z = -1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eLeft))
		{
			Key_Dir.x = 1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eRight))
		{
			Key_Dir.x = -1;
			m_Button = true;
		}

		Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

		//キー入力があれば
		if (Key_Dir.LengthSq() > 0)
		{
			if (Key_Dir.z == 1 && Key_Dir.z != -1 && Key_Dir.x != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed;
				m_Model.ChangeAnimation(5);
			}
			else if (Key_Dir.z == -1 && Key_Dir.z != 1 && Key_Dir.x != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed;
				m_Model.ChangeAnimation(8);
			}
			else if (Key_Dir.x == 1 && Key_Dir.x != -1 && Key_Dir.z != 1 && Key_Dir.z != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed;
				m_Model.ChangeAnimation(11);
			}
			else if (Key_Dir.x == -1 && Key_Dir.z != 1 && Key_Dir.z != 1 && Key_Dir.z != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed;
				m_Model.ChangeAnimation(12);
			}
			else if (Key_Dir.z == 1 && Key_Dir.x == 1 && Key_Dir.z != -1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed / 1.5;
				m_Model.ChangeAnimation(6);
			}
			else if (Key_Dir.z == 1 && Key_Dir.x == -1 && Key_Dir.z != -1 && Key_Dir.x != 1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed / 1.5;
				m_Model.ChangeAnimation(7);
			}
			else if (Key_Dir.z == -1 && Key_Dir.x == 1 && Key_Dir.z != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed / 1.5;
				m_Model.ChangeAnimation(9);
			}
			else if (Key_Dir.z == -1 && Key_Dir.x == -1 && Key_Dir.z != 1 && Key_Dir.x != 1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed / 1.5;
				m_Model.ChangeAnimation(10);
			}

		}
		else
		{
			//マウスの右を押していなかったら
			if (!CInput::GetState(0, CInput::eHold, CInput::eMouseR))
				m_Model.ChangeAnimation(0);
			m_Button = false;
		}

		//弾数が60以下で'R'を押すと
		if (CInput::GetState(0, CInput::ePush, CInput::eReload) && Bullet_Count < 60 && RemainingBullets::m_Remaining > 0)
			//リロード関数をtrue
			m_Reload = true;
		//リロード関数がtrueなら
		if (m_Reload)
		{
			m_Model.ChangeAnimation(1, 4, false, true,0,0);
			//アニメーションが終わると
			if (m_Model.isAnimationEnd(1))
			{
				Bullet_Refill = 60 - Bullet_Count;
				if (Bullet_Refill > RemainingBullets::m_Remaining)
				{
					Bullet_Refill = RemainingBullets::m_Remaining;
				}
				Bullet_Count += Bullet_Refill;
				RemainingBullets::m_Remaining -= Bullet_Refill;
				BulletNumber::m_Dansuu = Bullet_Count;
				//リロード関数をfalseにする
				m_Reload = false;
			}
		}
		else
		{
			//リロード関数がfalseなら{
			m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
		}

		//マウスの右を押すと
		if (CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			//攻撃状態へ
			m_State = eState_Attack;

		if (CInput::GetState(0, CInput::ePush, CInput::eChange1) && m_Reload == false && m_Button == false)
			//しゃがみ状態へ
			m_State = eState_Squat;

		if (Save::m_Pause == true)
			//ポーズ状態へ
			m_State = eState_Pause;

		if (ClearCollision::Switch::m_CameraSwitch == true)
			//イベント状態へ
			m_State = eState_Event;
	}
}

void Player::Squat()
{
	if (Mode::m_Squat == false)
	{
		m_Model.ChangeAnimation(23);
		Mode::m_Squat = true;
		if (m_Model.isAnimationEnd())
		{	
		}
	}

	if (Mode::m_Prone == true)
	{
		m_Model.ChangeAnimation(14);
		Mode::m_Squat = true;
		Mode::m_Prone = false;
		if (m_Model.isAnimationEnd())
		{
		}
	}

	else if (Mode::m_Squat == true)
	{
		Key_Dir = CVector3D(0, 0, 0);

		//マウス操作でキャラクターを回転
		Mouse_Vec = CInput::GetMouseVec();
		m_Rot.y += Mouse_Vec.x * -0.002f;
		m_Rot.x += Mouse_Vec.y * 0.002f;
		m_Rot.x = min(DtoR(45), max(DtoR(-45), m_Rot.x));

		//方向キーから入力方向ベクトルを設定
		if (CInput::GetState(0, CInput::eHold, CInput::eUp) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
		{
			Key_Dir.z = 1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eDown) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
		{
			Key_Dir.z = -1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eLeft) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
		{
			Key_Dir.x = 1;
			m_Button = true;
		}
		if (CInput::GetState(0, CInput::eHold, CInput::eRight) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
		{
			Key_Dir.x = -1;
			m_Button = true;
		}

		Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

		//キー入力があれば
		if (Key_Dir.LengthSq() > 0)
		{
			if (Key_Dir.z == 1 && Key_Dir.z != -1 && Key_Dir.x != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3;
				m_Model.ChangeAnimation(29);
			}
			else if (Key_Dir.z == -1 && Key_Dir.z != 1 && Key_Dir.x != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3;
				m_Model.ChangeAnimation(32);
			}
			else if (Key_Dir.x == 1 && Key_Dir.x != -1 && Key_Dir.z != 1 && Key_Dir.z != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3;
				m_Model.ChangeAnimation(35);
			}
			else if (Key_Dir.x == -1 && Key_Dir.x != 1 && Key_Dir.z != 1 && Key_Dir.z != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3;
				m_Model.ChangeAnimation(36);
			}
			else if (Key_Dir.z == 1 && Key_Dir.x == 1 && Key_Dir.z != -1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3 / 1.5;
				m_Model.ChangeAnimation(30);
			}
			else if (Key_Dir.z == 1 && Key_Dir.x == -1 && Key_Dir.z != -1 && Key_Dir.x != 1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3 / 1.5;
				m_Model.ChangeAnimation(31);
			}
			else if (Key_Dir.z == -1 && Key_Dir.x == 1 && Key_Dir.z != 1 && Key_Dir.x != -1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3 / 1.5;
				m_Model.ChangeAnimation(33);
			}
			else if (Key_Dir.z == -1 && Key_Dir.x == -1 && Key_Dir.z != 1 && Key_Dir.x != 1)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed3 / 1.5;
				m_Model.ChangeAnimation(34);
			}

		}
		else
		{
			m_Model.ChangeAnimation(25);
			m_Button = false;
		}

		//弾数が60以下で'R'を押すと
		if (CInput::GetState(0, CInput::ePush, CInput::eReload) && Bullet_Count < 60 && RemainingBullets::m_Remaining > 0)
			//リロード関数をtrue
			m_Reload = true;
		//リロード関数がtrueなら
		if (m_Reload)
		{
			m_Model.ChangeAnimation(1, 27, false, true,0,0);
			//アニメーションが終わると
			if (m_Model.isAnimationEnd(1))
			{
				Bullet_Refill = 60 - Bullet_Count;
				if (Bullet_Refill > RemainingBullets::m_Remaining)
				{
					Bullet_Refill = RemainingBullets::m_Remaining;
				}
				Bullet_Count += Bullet_Refill;
				RemainingBullets::m_Remaining -= Bullet_Refill;
				BulletNumber::m_Dansuu = Bullet_Count;
				//リロード関数をfalseにする
				m_Reload = false;
			}
		}
		else
		{
			//リロード関数がfalseなら
				m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
		}

		//マウスの右を押すと
		if (CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			//攻撃状態へ
			m_State = eState_Attack;

		if (CInput::GetState(0, CInput::eHold, CInput::eChange2) && CInput::GetState(0, CInput::ePush, CInput::eChange1) && m_Reload == false && m_Button == false)
			//通常状態へ
			m_State = eState_Idle;

		if (!CInput::GetState(0, CInput::eHold, CInput::eChange2) && CInput::GetState(0, CInput::ePush, CInput::eChange1) && m_Reload == false && m_Button == false)
			//伏せ状態へ
			m_State = eState_Prone;

		if (ClearCollision::Switch::m_CameraSwitch == true)
			//イベント状態へ
			m_State = eState_Event;
	}
}

void Player::Prone()
{
	if (Mode::m_Prone == false)
	{
		m_Model.ChangeAnimation(13);
		Mode::m_Prone = true;
		Mode::m_Squat = false;
		if (m_Model.isAnimationEnd())
		{
		}
	}

	if (Mode::m_Prone == true)
	{
		Key_Dir = CVector3D(0, 0, 0);

		//マウス操作でキャラクターを回転
		Mouse_Vec = CInput::GetMouseVec();
		m_Rot.y += Mouse_Vec.x * -0.002f;
		m_Rot.x += Mouse_Vec.y * 0.002f;
		m_Rot.x = min(DtoR(15), max(DtoR(-3), m_Rot.x));

		if (m_Reload == false)
		{
			//方向キーから入力方向ベクトルを設定
			if (CInput::GetState(0, CInput::eHold, CInput::eUp) && Key_Dir.z != -1 && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			{
				Key_Dir.z = 1;
				m_Button = true;
			}
			if (CInput::GetState(0, CInput::eHold, CInput::eDown) && Key_Dir.z != 1 && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			{
				Key_Dir.z = -1;
				m_Button = true;
			}
			if (CInput::GetState(0, CInput::eHold, CInput::eLeft) && Key_Dir.z != 1 && Key_Dir.z != -1 && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			{
				Key_Dir.x = 1;
				m_Button = true;
				//回転状態へ
				m_State = eState_Rotate;
			}
			if (CInput::GetState(0, CInput::eHold, CInput::eRight) && Key_Dir.z != 1 && Key_Dir.z != -1 && !CInput::GetState(0, CInput::eHold, CInput::eMouseR))
			{
				Key_Dir.x = -1;
				m_Button = true;
				//回転状態へ
				m_State = eState_Rotate;
			}
		}

		Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

		//キー入力があれば
		if (Key_Dir.LengthSq() > 0)
		{
			if (Key_Dir.z == 1 && Key_Dir.z != -1 && Key_Dir.x != 1 && Key_Dir.x != -1 && Roll::m_RollLeft == false && Roll::m_RollRight == false)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed5;
				m_Model.ChangeAnimation(19);
			}
			else if (Key_Dir.z == -1 && Key_Dir.z != 1 && Key_Dir.x != 1 && Key_Dir.x != -1 && Roll::m_RollLeft == false && Roll::m_RollRight == false)
			{
				//移動処理 回転行列×移動方向
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Speed5;
				m_Model.ChangeAnimation(21);
			}
		}
		else
		{
			m_Model.ChangeAnimation(15);
			m_Button = false;
		}

		//弾数が60以下で'R'を押すと
		if (CInput::GetState(0, CInput::ePush, CInput::eReload) && Bullet_Count < 60 && RemainingBullets::m_Remaining > 0)
			//リロード関数をtrue
			m_Reload = true;
			//リロード関数がtrueなら
		if (m_Reload)
		{
			m_Model.ChangeAnimation(1, 17, false, true,0,0);
			//アニメーションが終わると
			if (m_Model.isAnimationEnd())
			{
				Bullet_Refill = 60 - Bullet_Count;
				if (Bullet_Refill > RemainingBullets::m_Remaining)
				{
					Bullet_Refill = RemainingBullets::m_Remaining;
				}
				Bullet_Count += Bullet_Refill;
				RemainingBullets::m_Remaining -= Bullet_Refill;
				BulletNumber::m_Dansuu = Bullet_Count;
				//リロード関数をfalseにする
				m_Reload = false;
			}
		}
		else
		{
			//リロード関数がfalseなら{
			m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
		}

		//マウスの右を押すと
		if (CInput::GetState(0, CInput::eHold, CInput::eMouseR) && m_Button == false)
			//攻撃状態へ
			m_State = eState_Attack;
		
		if (CInput::GetState(0, CInput::eHold, CInput::eChange2) && CInput::GetState(0, CInput::ePush, CInput::eChange1) && m_Reload == false && m_Button == false)
			//しゃがみ状態へ
			m_State = eState_Squat;
			
		if (ClearCollision::Switch::m_CameraSwitch == true)
			//イベント状態へ
			m_State = eState_Event;
	}
}

void Player::Rotate()
{
	if (Key_Dir.LengthSq() > 0)
	{
		if (Key_Dir.x == 1 && Key_Dir.x != -1 && Key_Dir.z != 1 && Key_Dir.z != -1)
		{
			m_Model.ChangeAnimation(20);
			if (m_Model.GetAnimationFrame() > 0 && m_Model.GetAnimationFrame() < 40)
				Roll::m_RollLeft = true;
			else
				Roll::m_RollLeft = false;

			if (Roll::m_RollLeft == true && !m_Model.isAnimationEnd())
			{
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Roll;
			}

			else if (m_Model.isAnimationEnd())
			{
				Roll::m_RollLeft = false;
			}
		}

		if (Key_Dir.x == -1 && Key_Dir.x != 1 && Key_Dir.z != 1 && Key_Dir.z != -1)
		{
			m_Model.ChangeAnimation(22);
			if (m_Model.GetAnimationFrame() > 0 && m_Model.GetAnimationFrame() < 50)
				Roll::m_RollRight = true;
			else
				Roll::m_RollRight = false;

			if (Roll::m_RollRight == true && !m_Model.isAnimationEnd())
			{
				Dir = Rot_Matrix * Key_Dir;
				m_Pos += Dir * Move_Roll / 1.1;
			}

			else if (m_Model.isAnimationEnd())
			{
				Roll::m_RollRight = false;
			}
		}
	}

	if (Roll::m_RollLeft == false && Roll::m_RollRight == false)
	{
		//伏せ状態へ
		m_State = eState_Prone;
	}

	if (ClearCollision::Switch::m_CameraSwitch == true)
		//イベント状態へ
		m_State = eState_Event;
}

void Player::Attack()
{
	if (CInput::GetState(0, CInput::eHold, CInput::eMouseR)) 
	{

		//弾数が60以下でマウスの左を押していない状態で'R'を押すと
		if (CInput::GetState(0, CInput::ePush, CInput::eReload) && !CInput::GetState(0, CInput::eHold, CInput::eMouseL) && Bullet_Count < 60 && RemainingBullets::m_Remaining > 0)
			//リロード関数をtrueに
			m_Reload = true;

		if (Bullet_Count == 0 && CInput::GetState(0, CInput::eHold, CInput::eMouseL) && RemainingBullets::m_Remaining > 0)
			//リロード関数をtrueに
			m_Reload = true;

		if (Mode::m_Squat == false && Mode::m_Prone == false)
		{
			Key_Dir = CVector3D(0, 0, 0);

			//マウス操作でキャラクターを回転
			Mouse_Vec = CInput::GetMouseVec();
			m_Rot.y += Mouse_Vec.x * -0.002f;
			m_Rot.x += Mouse_Vec.y * 0.002f;
			m_Rot.x = min(DtoR(45), max(DtoR(-45), m_Rot.x));

			//方向キーから入力方向ベクトルを設定
			if (CInput::GetState(0, CInput::eHold, CInput::eUp))
				Key_Dir.z = 1;
			if (CInput::GetState(0, CInput::eHold, CInput::eDown))
				Key_Dir.z = -1;
			if (CInput::GetState(0, CInput::eHold, CInput::eLeft))
				Key_Dir.x = 1;
			if (CInput::GetState(0, CInput::eHold, CInput::eRight))
				Key_Dir.x = -1;

			Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

			//リロード関数がfalseなら
			if (m_Reload == false)
			{
				/* 射線を表示 */
				Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

				Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));
			}

			//キー入力があれば
			if (Key_Dir.LengthSq() > 0)
			{
				if (Key_Dir.z == 1 && Key_Dir.x != 1 && Key_Dir.x != -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2;
					m_Model.ChangeAnimation(5);
				}
				else if (Key_Dir.z == -1 && Key_Dir.x != 1 && Key_Dir.x != -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2;
					m_Model.ChangeAnimation(8);
				}
				else if (Key_Dir.x == 1 && Key_Dir.z != 1 && Key_Dir.z != -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2;
					m_Model.ChangeAnimation(11);
				}
				else if (Key_Dir.x == -1 && Key_Dir.z != 1 && Key_Dir.z != -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2;
					m_Model.ChangeAnimation(12);
				}
				else if (Key_Dir.z == 1 && Key_Dir.x == 1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2 / 1.5;
					m_Model.ChangeAnimation(6);
				}
				else if (Key_Dir.z == 1 && Key_Dir.x == -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2 / 1.5;
					m_Model.ChangeAnimation(7);
				}
				else if (Key_Dir.z == -1 && Key_Dir.x == 1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2 / 1.5;
					m_Model.ChangeAnimation(9);
				}
				else if (Key_Dir.z == -1 && Key_Dir.x == -1)
				{
					//移動処理 回転行列×移動方向
					Dir = Rot_Matrix * Key_Dir;
					m_Pos += Dir * Move_Speed2 / 1.5;
					m_Model.ChangeAnimation(10);
				}
			}
			else
			{
				m_Model.ChangeAnimation(3);
			}

			//(弾数が0以上、'R'を押していない状態、リロード関数がfalse)なら
			if (Bullet_Count > 0 && !CInput::GetState(0, CInput::ePush, CInput::eReload) && m_Reload == false)
			{
				//マウスの左を押すと
				if (CInput::GetState(0, CInput::eHold, CInput::eMouseL))
				{
					//射撃関数をtrueに
					m_Shot = true;

					/* 射線を表示 */
					Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

					Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));

					//射撃関数がtrueなら
					if (m_Shot)
					{
						if (Bullet_Interval % 5 == 0)
						{
							//武器の先端から銃弾を発射
							Base::Add(new PlayerAttack(Wepon_Pos, CMatrix::MRotation(m_Rot).GetFront()));
							//弾数を減らす
							Bullet_Count -= 1;
							BulletNumber::m_Dansuu -= 1;
							//マウスの左を離すと
							if (!CInput::GetState(0, CInput::eHold, CInput::eMouseL))
							{
								//射撃関数をfalseに
								m_Shot = false;
							}
						}
						Bullet_Interval++;
					}
					else
					{
						//射撃関数がfalseなら
					}
				}
			}

			//リロード関数がtrueなら
			if (m_Reload)
			{
				m_Model.ChangeAnimation(1, 4, false, true,0,0);
				//アニメーションが終わると
				if (m_Model.isAnimationEnd(1))
				{
					Bullet_Refill = 60 - Bullet_Count;
					if (Bullet_Refill > RemainingBullets::m_Remaining)
					{
						Bullet_Refill = RemainingBullets::m_Remaining;
					}
					Bullet_Count += Bullet_Refill;
					RemainingBullets::m_Remaining -= Bullet_Refill;
					BulletNumber::m_Dansuu = Bullet_Count;
					//リロード関数をfalseにする
					m_Reload = false;
				}
			}
			else
			{
				m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
			}
			if (ClearCollision::Switch::m_CameraSwitch == true)
				m_State = eState_Event;
		}

		if (Mode::m_Squat == true)
		{
			Key_Dir = CVector3D(0, 0, 0);

			//マウス操作でキャラクターを回転
			Mouse_Vec = CInput::GetMouseVec();
			m_Rot.y += Mouse_Vec.x * -0.002f;
			m_Rot.x += Mouse_Vec.y * 0.002f;
			m_Rot.x = min(DtoR(45), max(DtoR(-45), m_Rot.x));

			Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

			//リロード関数がfalseなら
			if (m_Reload == false)
			{
				/* 射線を表示 */
				Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

				Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));
			}

			//(弾数が0以上、'R'を押していない状態、リロード関数がfalse)なら
			if (Bullet_Count > 0 && !CInput::GetState(0, CInput::ePush, CInput::eReload) && m_Reload == false)
			{
				//マウスの左を押すと
				if (CInput::GetState(0, CInput::eHold, CInput::eMouseL))
				{
					//射撃関数をtrueに
					m_Shot = true;

					/* 射線を表示 */
					Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

					Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));

					//射撃関数がtrueなら
					if (m_Shot)
					{
						if (Bullet_Interval % 5 == 0)
						{
							//武器の先端から銃弾を発射
							Base::Add(new PlayerAttack(Wepon_Pos, CMatrix::MRotation(m_Rot).GetFront()));
							//弾数を減らす
							Bullet_Count -= 1;
							BulletNumber::m_Dansuu -= 1;
							//マウスの左を離すと
							if (!CInput::GetState(0, CInput::eHold, CInput::eMouseL))
							{
								//射撃関数をfalseに
								m_Shot = false;
							}
						}
						Bullet_Interval++;
					}
					else
					{
						//射撃関数がfalseなら
					}
				}
			}

			//リロード関数がtrueなら
			if (m_Reload)
			{
				m_Model.ChangeAnimation(1, 27, false, true,0,0);
				//アニメーションが終わると
				if (m_Model.isAnimationEnd(1))
				{
					Bullet_Refill = 60 - Bullet_Count;
					if (Bullet_Refill > RemainingBullets::m_Remaining)
					{
						Bullet_Refill = RemainingBullets::m_Remaining;
					}
					Bullet_Count += Bullet_Refill;
					RemainingBullets::m_Remaining -= Bullet_Refill;
					BulletNumber::m_Dansuu = Bullet_Count;
					//リロード関数をfalseにする
					m_Reload = false;
				}
			}
			else
			{
				m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
			}
			if (ClearCollision::Switch::m_CameraSwitch == true)
				//イベント状態へ
				m_State = eState_Event;
		}

		if (Mode::m_Prone == true)
		{
			//マウス操作でキャラクターを回転
			Mouse_Vec = CInput::GetMouseVec();
			m_Rot.y += Mouse_Vec.x * -0.002f;
			m_Rot.x += Mouse_Vec.y * 0.002f;
			m_Rot.x = min(DtoR(5), max(DtoR(-5), m_Rot.x));

			Rot_Matrix = CMatrix::MRotationY(m_Rot.y);

			//リロード関数がfalseなら
			if (m_Reload == false)
			{
				/* 射線を表示 */
				Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

				Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));
			}

			//(弾数が0以上、'R'を押していない状態、リロード関数がfalse)なら
			if (Bullet_Count > 0 && !CInput::GetState(0, CInput::ePush, CInput::eReload) && m_Reload == false)
			{
				//マウスの左を押すと
				if (CInput::GetState(0, CInput::eHold, CInput::eMouseL))
				{
					//射撃関数をtrueに
					m_Shot = true;

					/* 射線を表示 */
					Wepon_Pos = m_Wepon_Class.Player_Wepon_Matrix * CVector4D(0, 0, 44, 1);

					Utility::DrawLine(Wepon_Pos, Wepon_Pos + CMatrix::MRotation(m_Rot).GetFront() * 50, CVector4D(1, 0, 0, 1));

					//射撃関数がtrueなら
					if (m_Shot)
					{
						//m_Model.ChangeAnimation(1, 16, false);
						if (Bullet_Interval % 5 == 0)
						{
							//武器の先端から銃弾を発射
							Base::Add(new PlayerAttack(Wepon_Pos, CMatrix::MRotation(m_Rot).GetFront()));
							//弾数を減らす
							Bullet_Count -= 1;
							BulletNumber::m_Dansuu -= 1;
							//マウスの左を離すと
							if (!CInput::GetState(0, CInput::eHold, CInput::eMouseL))
							{
								//射撃関数をfalseに
								m_Shot = false;
							}
						}
						Bullet_Interval++;
					}
					else
					{
						//射撃関数がfalseなら
					}
				}
			}
			//リロード関数がtrueなら
			if (m_Reload)
			{
				m_Model.ChangeAnimation(1, 17, false,true,0,0);
				//アニメーションが終わると
				if (m_Model.isAnimationEnd())
				{
					Bullet_Refill = 60 - Bullet_Count;
					if (Bullet_Refill > RemainingBullets::m_Remaining)
					{
						Bullet_Refill = RemainingBullets::m_Remaining;
					}
					Bullet_Count += Bullet_Refill;
					RemainingBullets::m_Remaining -= Bullet_Refill;
					BulletNumber::m_Dansuu = Bullet_Count;
					//リロード関数をfalseにする
					m_Reload = false;
				}
			}
			else
			{
				m_Model.ChangeAnimation(1, m_Model.GetAnimationJam(), true, true, m_Model.GetAnimationFrame());
			}
			if (ClearCollision::Switch::m_CameraSwitch == true)
				//イベント状態へ
				m_State = eState_Event;
		}
	}
	//マウスの右を離すと
	else if (!CInput::GetState(0, CInput::eHold, CInput::eMouseR) && Mode::m_Squat == false && Mode::m_Prone == false)
	{
		//通常状態へ
		m_State = eState_Idle;
	}
	//マウスの右を離すと
	else if (!CInput::GetState(0, CInput::eHold, CInput::eMouseR) && Mode::m_Squat == true)
	{
		//しゃがみ状態へ
		m_State = eState_Squat;
	}
	//マウスの右を離すと
	else if (!CInput::GetState(0, CInput::eHold, CInput::eMouseR) && Mode::m_Prone == true)
	{
		//伏せ状態へ
		m_State = eState_Prone;
	}
}

void Player::Damage()
{
	if (CInput::GetState(0, CInput::eHold, CInput::eMouseR))
	{
		//攻撃状態へ
		m_State = eState_Attack;
		m_HitCount = 0;
	}
	else
	{
		if (Mode::m_Squat == false && Mode::m_Prone == false)
		{
			//通常状態へ
			m_State = eState_Idle;
			m_HitCount = 0;
		}

		if (Mode::m_Squat == true)
		{
			//しゃがみ状態へ
			m_State = eState_Squat;
			m_HitCount = 0;
		}
		
		if (Mode::m_Prone == true)
		{
			//伏せ状態へ
			m_State = eState_Prone;
			m_HitCount = 0;
		}
	}
}

void Player::Down()
{
	if (Mode::m_Squat == false)
	{
		m_Model.ChangeAnimation(2);
		if (m_Model.isAnimationEnd())
		{
			m_Kill = true;
			if (m_Kill == true)
			{
				Base::KillALL();
				Base::Add(new GameOver());
			}
		}
	}
	if (Mode::m_Squat == true)
	{
		m_Model.ChangeAnimation(28);
		if (m_Model.isAnimationEnd())
		{
			m_Kill = true;
			if (m_Kill == true)
			{
				Base::KillALL();
				Base::Add(new GameOver());
			}
		}
	}
	if (Mode::m_Prone == true)
	{
		m_Model.ChangeAnimation(18);
		if (m_Model.isAnimationEnd())
		{
			m_Kill = true;
			if (m_Kill == true)
			{
				Base::KillALL();
				Base::Add(new GameOver());
			}
		}
	}
}

void Player::Menu()
{
	if (Save::m_Pause == true)
	{
		m_Model.ChangeAnimation(1, 0);
		m_Model.ChangeAnimation(0);
	}

	if (Save::m_Pause == false)
	{
		//通常状態へ
		m_State = eState_Idle;
	}
}

void Player::Event()
{
	if (ClearCollision::Switch::m_CameraSwitch == true && Title::Screen::m_Title == false)
	{
		//printf("終了");
		if (m_Count == 0)
			m_Pos = CVector3D(-47, 8, -41);
		if (m_Count < 150)
		{
			m_Rot = CVector3D(0, DtoR(180), 0);
			m_Pos += CVector3D(0, 0, -1) * Move_Speed4;
			m_Model.ChangeAnimation(1, 5);
			m_Model.ChangeAnimation(5);
			m_Count++;
		}
		else
		{
			m_Model.ChangeAnimation(1, 3);
			m_Model.ChangeAnimation(3);
			Player::Switch::m_GameClear = true;
		}
	}

	if (Title::Screen::m_Title == true)
	{
		m_Rot = CVector3D(0, DtoR(135), 0);
		m_Pos = CVector3D(0, 0, 1);
	}

	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Pos = CVector3D(45, 0, 48);
		//通常状態へ
		m_State = eState_Idle;
	}

	if (Title::Switch::m_SaveStart == true && ClearCollision::Switch::m_CameraSwitch == false)
	{
		m_Pos = CVector3D(-47, 4, 15);
		m_Rot = CVector3D(0, DtoR(-90), 0);
		//通常状態へ
		m_State = eState_Idle;
	}
}

void Player::Render()
{
	CLight::SetLighting(false);
	m_Model.SetPos(m_Pos);
	m_Model.SetRot(0, m_Rot.y, 0);
	m_Model.SetScale(0.01f, 0.01f, 0.01f);
	if (Mode::m_Prone == false)
		m_Model.BindFrameMatrix(5, CMatrix::MRotation(m_Rot));
	else
		m_Model.UnbindFrameMatrix(5);
		
	m_Model.Render();

	//武器の行列を設定(手に持たせる)
	//手のボーン行列[親] * 武器のローカル行列[子](平行移動 * 回転 * スケール)
	//m_Wepon_Class.Player_Wepon_Matrix = m_Model.GetFrameMatrix(31) * CMatrix::MTranselate(-17.981f, -5.383f, 7.500f) * CMatrix::MRotation(DtoR(90), 0, DtoR(-90));

	if (m_State == eState_Attack && m_Reload == false)
	{
		m_Wepon_Class.Player_Wepon_Matrix = CMatrix::MTranselate((m_Model.GetFrameMatrix(42) * CMatrix::MTranselate(2.5f, 17.0f, 0.0f)).GetPosition()) * CMatrix::MRotation(m_Rot) * CMatrix::MScale(0.01, 0.01, 0.01);
	} 
	else 
	{
		m_Wepon_Class.Player_Wepon_Matrix = m_Model.GetFrameMatrix(42) * CMatrix::MTranselate(2.5f, 17.0f, 0.0f) * CMatrix::MRotation(DtoR(10), DtoR(-90), DtoR(-90)) * CMatrix::MScale(0.95, 0.95, 0.95);
	}
	m_Wepon_Class.Render();

	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
	//FONT_T()->Draw(0, 32, 1, 0, 0, "%d %d", m_Model.GetAnimationJam(0), m_Model.GetAnimationJam(1));
	CLight::SetLighting(true);
}

void Player::Draw()
{
	if (Title::Screen::m_Title == false && ClearCollision::Switch::m_CameraSwitch == false)
	{
		if (m_Hp_Now <= 100)
		{
			m_Life[0].SetPos(1665, 845);
			m_Life[0].SetSize(200, 50);
			m_Life[0].Draw();
		}
		if (m_Hp_Now <= 90)
		{
			m_Life[1].SetPos(1665, 845);
			m_Life[1].SetSize(200, 50);
			m_Life[1].Draw();
		}
		if (m_Hp_Now <= 80)
		{
			m_Life[2].SetPos(1665, 845);
			m_Life[2].SetSize(200, 50);
			m_Life[2].Draw();
		}
		if (m_Hp_Now <= 70)
		{
			m_Life[3].SetPos(1665, 845);
			m_Life[3].SetSize(200, 50);
			m_Life[3].Draw();
		}
		if (m_Hp_Now <= 60)
		{
			m_Life[4].SetPos(1665, 845);
			m_Life[4].SetSize(200, 50);
			m_Life[4].Draw();
		}
		if (m_Hp_Now <= 50)
		{
			m_Life[5].SetPos(1665, 845);
			m_Life[5].SetSize(200, 50);
			m_Life[5].Draw();
		}
		if (m_Hp_Now <= 40)
		{
			m_Life[6].SetPos(1665, 845);
			m_Life[6].SetSize(200, 50);
			m_Life[6].Draw();
		}
		if (m_Hp_Now <= 30)
		{
			m_Life[7].SetPos(1665, 845);
			m_Life[7].SetSize(200, 50);
			m_Life[7].Draw();
		}
		if (m_Hp_Now <= 20)
		{
			m_Life[8].SetPos(1665, 845);
			m_Life[8].SetSize(200, 50);
			m_Life[8].Draw();
		}
		if (m_Hp_Now <= 10)
		{
			m_Life[9].SetPos(1665, 845);
			m_Life[9].SetSize(200, 50);
			m_Life[9].Draw();
		}
		if (m_Hp_Now <= 0)
		{
			m_Life[10].SetPos(1665, 845);
			m_Life[10].SetSize(200, 50);
			m_Life[10].Draw();
		}

		if (Hyouzi::m_Hyouzi1 == true)
		{
			m_Img[0].SetPos(850, 550);
			m_Img[0].SetSize(100, 50);
			m_Img[0].Draw();
		}

		if (Hyouzi::m_Hyouzi2 == true)
		{
			m_Img[1].SetPos(1000, 550);
			m_Img[1].SetSize(200, 150);
			m_Img[1].Draw();
		}
	}

}

void Player::Collision(Base* B)
{
	switch (B->GetTypeId())
	{
	case eId_Hit2:
		if (CollisionCapsule(this, B))
		{
			ClearCollision::Hit::m_CollisionHit = true;
		}
		break;

	case eId_HitCollision1:
		if (CollisionCapsule(this, B))
		{
			EnemyCollision::Hit::m_CollisionHit = true;
		}
		break;

	case eId_HitCollision2:
		if (CollisionCapsule(this, B))
		{
			BossCollision::Hit::m_CollisionHit = true;
		}
		break;

	case eId_AmmoBox:
		if (CollisionCapsule(this, B))
		{
			Hyouzi::m_Hyouzi1 = true;
			Hyouzi::m_Hyouzi2 = true;
			if (CInput::GetState(0, CInput::ePush, CInput::eGet) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR) && m_Reload == false)
			{
				B->m_Kill = true;
				if (RemainingBullets::m_Remaining <= 999)
				{
					RemainingBullets::m_Remaining += 30;
					Hyouzi::m_Hyouzi1 = false;
					Hyouzi::m_Hyouzi2 = false;
				}
				if (RemainingBullets::m_Remaining > 999)
				{
					RemainingBullets::m_Remaining = 300;
					Hyouzi::m_Hyouzi1 = false;
					Hyouzi::m_Hyouzi2 = false;
				}
			}
		}
		if (!CollisionCapsule(this, B))
		{
			Hyouzi::m_Hyouzi1 = false;
			Hyouzi::m_Hyouzi2 = false;
		}
		//else 
		//{
		//	m_Space = false;
		//	Hyouzi1 = false;
		//}
		break;

	case eId_Key1:
		if (CollisionCapsule(this, B))
		{
			Hyouzi::m_Hyouzi1 = true;
			if (CInput::GetState(0, CInput::ePush, CInput::eGet) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR) && m_Reload == false)
			{
				Hyouzi::m_Hyouzi1 = false;
				B->m_Kill = true;
				GetKey::m_Key1 = true;
				Key1_Count = 1;
			}
		}
		break;

	case eId_Key2:
		if (CollisionCapsule(this, B))
		{
			Hyouzi::m_Hyouzi1 = true;
			if (CInput::GetState(0, CInput::ePush, CInput::eGet) && !CInput::GetState(0, CInput::eHold, CInput::eMouseR) && m_Reload == false)
			{
				Hyouzi::m_Hyouzi1 = false;
				B->m_Kill = true;
				GetKey::m_Key2 = true;
				Key2_Count = 1;
			}
		}
		break;

	case eId_Door1:
		if (CollisionOBBShpere(B, this) && Door1::Mode::m_OpenDoor1 == false)
		{
			m_Pos.x = m_Pos_Old.x;
			m_Pos.z = m_Pos_Old.z;
		}
		break;

	case eId_Door2:
		if (CollisionOBBShpere(B, this) && Door2::Mode::m_OpenDoor2 == false)
		{
			m_Pos.x = m_Pos_Old.x;
			m_Pos.z = m_Pos_Old.z;
		}
		break;

	case eId_SaveSpot:
		if (CollisionOBBShpere(B, this))
		{
			m_Pos.x = m_Pos_Old.x;
			m_Pos.z = m_Pos_Old.z;
		}
		break;

	case eId_Zombie:
		if (Base* Z = Base::FindObject(eId_Zombie))
		{
			if (Z->m_Death == false)
			{
				CollisionCharctor(B);
			}
			//弱攻撃
			if (Z->m_Attack1 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad) && m_HitCount == 0)
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 5;

					m_HitCount++;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}
			}

			//強攻撃
			else if (Z->m_Attack2 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad) && m_HitCount == 0)
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 15;

					m_HitCount++;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}

			}
		}
		break;

	case eId_BossEnemy:
		if (Base* Boss = Base::FindObject(eId_BossEnemy))
		{
			CollisionCharctor(B);
			/* 発見時 */
			//弱攻撃
			if (BossEnemy::Mode::m_Hakken == true && Boss->m_Attack1 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad))
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 10;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}
			}

			//強攻撃
			else if (BossEnemy::Mode::m_Hakken == true && Boss->m_Attack2 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad))
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 30;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}

			}

			/* 怒り時 */
			//弱攻撃
			else if (BossEnemy::Mode::m_Ikari == true && Boss->m_Attack1 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad))
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 30;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}
			}
			 //強攻撃
			else if (BossEnemy::Mode::m_Ikari == true && Boss->m_Attack2 == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad))
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 50;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}
			}

			//ジャンプ攻撃
			else if (BossEnemy::Mode::m_Jump == true && CCollision::CollisionCapsule(B->LineS, B->LineE, B->m_Rad, LineS, LineE, m_Rad))
			{
				if (m_Hit_Id != B->m_Hit_Id)
				{
					m_Hit_Id = B->m_Hit_Id;
					m_Hp_Now -= 70;

					if (m_Hp_Now > 0)
					{
						//ダメージ状態へ
						m_State = eState_Damage;
					}
					if (m_Hp_Now <= 0)
					{
						//死亡状態へ
						m_State = eState_Down;
					}
				}
			}
		}
		break;

	case eId_TutorialField:
		//フィールドとの衝突
		CollisionField(B->GetModel());
		break;
	}
}
