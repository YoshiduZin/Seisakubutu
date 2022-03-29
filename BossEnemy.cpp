#include "BossEnemy.h"
#include "Key.h"

/* ボスのモード */
bool BossEnemy::Mode::m_Hakken = false;	//発見
bool BossEnemy::Mode::m_Ikari = false;	//怒り
bool BossEnemy::Mode::m_Jump = false;	//ジャンプ

BossEnemy::BossEnemy(const CVector3D& P) : Base(eId_BossEnemy)
{
	m_Pos = P;
	m_BossEnemy = COPY_RESOURCE("BossEnemy", CModelA3M);
	m_Rad = 0.7f;
	m_Hp = 100;

	//Y軸の角度
	View_Ang_Y = DtoR(45);
	View_Ang_X = DtoR(30);

	View_Length = 10;

	m_Check = false;

	//はじめは通常状態へ
	m_State = eState_Idle;
}

void BossEnemy::Update()
{
	//状態の切り替え
	switch (m_State)
	{
	case eState_Idle:
		Idle();	//通常状態へ
		break;
	case eState_Mihakken:
		Mihakken();
		break;   //未発見状態
	case eState_Hakken:
		Hakken();//発見状態へ
		break;
	case eState_Ikari:
		Ikari();  //怒り状態へ
		break;
	case eState_Attack1:
		Attack1();//弱攻撃状態へ
		break;
	case eState_Attack2:
		Attack2();//強攻撃状態へ
		break;
	case eState_Attack3:
		Attack3();//ジャンプ攻撃状態へ
		break;
	case eState_Damage:
		Damage();//ダメージ状態
		break;
	case eState_Down:
		Down();	 //死亡状態へ
		break;
	}

	LineS = m_Pos + CVector3D(0, 0.75, 0);
	LineE = m_Pos + CVector3D(0, 2, 0);

	m_BossEnemy.UpdateAnimation();

	m_Vec.y -= GRVITY;
	m_Pos += m_Vec;

	View_Dir = CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y));
}

void BossEnemy::Idle()
{
	if (Base* Player = Base::FindObject(eId_Player))
	{
		if (Base* Field = Base::FindObject(eId_TutorialField))
		{
			/* ボスからプレイヤーへの距離 */
			LVec = Player->m_Pos - m_Pos;
			Length = LVec.Length();

			/* ボスからプレイヤーへの方向と角度 */
			AVec = LVec / LVec.Length();
			D = CVector3D::Dot(View_Dir, AVec);
			if (D >= 1)
				D = 1;
			Ang = acos(D);

			if (Ang <= View_Ang_Y && Ang <= View_Ang_X && Length <= View_Length)
			{
				m_State = eState_Hakken;
			}
			else
			{
				m_State = eState_Mihakken;
			}
		}
	}
}

void BossEnemy::Mihakken()
{
	static CVector3D RoutePoint1[4] =
	{
		CVector3D(10,0,0),
		CVector3D(0,0,10),
		CVector3D(-10,0,0),
		CVector3D(0,0,-10),
	};
	
	if (Base* Player = Base::FindObject(eId_Player))
	{
		/* ボスからプレイヤーへの距離 */
		LVec = Player->m_Pos - m_Pos;
		Length = LVec.Length();

		/* ボスからプレイヤーへの方向と角度 */
		AVec = LVec / LVec.Length();
		D = CVector3D::Dot(View_Dir, AVec);
		if (D >= 1)
			D = 1;
		Ang = acos(D);

		if (Ang <= View_Ang_Y && Ang <= View_Ang_X && Length <= View_Length)
		{
				m_State = eState_Hakken;
		}
		else
		{
			LVec = RoutePoint1[Point] - m_Pos;
			Length = LVec.Length();

			m_Rot.y = atan2(LVec.x, LVec.z);
			m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed;
			m_BossEnemy.ChangeAnimation(1);
			if (Length < 1)
				Point++;
			if (Point > 3)
				Point = 0;
		}
	}
}

void BossEnemy::Hakken()
{
	if (Mode::m_Hakken == false)
	{
		m_BossEnemy.ChangeAnimation(2);
		if (m_BossEnemy.isAnimationEnd())
			Mode::m_Hakken = true;
	}

	if (Mode::m_Hakken == true)
	{
		if (Base* Player = Base::FindObject(eId_Player))
		{
			Vec = Player->GetPos() - m_Pos;
			Length = Vec.LengthSq();
			m_Rot.y = atan2(Vec.x, Vec.z);
			m_BossEnemy.ChangeAnimation(3);
			if (Length > 1.25)
				m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed2;
			if (Length <= 1.25)
			{
				if (rand() % 100 < 50)
				{
					m_State = eState_Attack1;
				}

				else if (rand() % 100 < 20 )
				{
					m_State = eState_Attack2;
				}
			}
		}
	}
}

void BossEnemy::Ikari()
{
	if (Mode::m_Ikari == false)
	{
		m_BossEnemy.ChangeAnimation(7);
		if (m_BossEnemy.isAnimationEnd())
			Mode::m_Ikari = true;
	}

	if (Mode::m_Ikari == true)
	{
		if (Base* Player = Base::FindObject(eId_Player))
		{
			Vec = Player->GetPos() - m_Pos;
			Length = Vec.LengthSq();
			m_Rot.y = atan2(Vec.x, Vec.z);
			m_BossEnemy.ChangeAnimation(3);
			
			if (Length > 80)
			{
				//if (rand() % 100 < 80)
				//{
				//	m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed4;
				//}
				//if (rand() % 100 < 20)
				//{
					m_State = eState_Attack3;
				//}
			}

			if (Length > 1.3)
			{
				if (rand() % 100 < 50)
				{
					m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed3;
				}
			}
			
			if (Length <= 1.3)
			{
				if (rand() % 100 < 50)
				{
					m_State = eState_Attack1;
				}

				else if (rand() % 100 < 20)
				{
					m_State = eState_Attack2;
				}
			}
		}
	}
}

void BossEnemy::Attack1()
{
	m_BossEnemy.ChangeAnimation(4);
	if (m_BossEnemy.GetAnimationFrame() > 8 && m_BossEnemy.GetAnimationFrame() < 12)
		m_Attack1 = true;
	else
		m_Attack1 = false;
	if (m_BossEnemy.isAnimationEnd())
	{
		m_Hit_Id += 1;
		if (m_Hp > 50)
		{
			m_State = eState_Hakken;
			m_Attack1 = false;
		}

		if (m_Hp <= 50)
		{
			m_State = eState_Ikari;
			m_Attack1 = false;
		}
	}
}

void BossEnemy::Attack2()
{
	m_BossEnemy.ChangeAnimation(5);
	if (m_BossEnemy.GetAnimationFrame() > 38 && m_BossEnemy.GetAnimationFrame() < 47)
		m_Attack2 = true;
	else
		m_Attack2 = false;
	if (m_BossEnemy.isAnimationEnd())
	{
		m_Hit_Id += 1;
		if (m_Hp > 50)
		{
			m_State = eState_Hakken;
			m_Attack2 = false;
		}

		if (m_Hp <= 50)
		{
			m_State = eState_Ikari;
			m_Attack2 = false;
		}
	}
}

void BossEnemy::Attack3()
{
	m_Check = true;
	m_BossEnemy.ChangeAnimation(6);
	if (m_BossEnemy.GetAnimationFrame() > 18 && m_BossEnemy.GetAnimationFrame() < 48)
		Mode::m_Jump = true;
	else
		Mode::m_Jump = false;
	
	if (Mode::m_Jump == true && !m_BossEnemy.isAnimationEnd())
	{
		if (Base* Player = Base::FindObject(eId_Player))
		{
			Vec = Player->GetPos() - m_Pos;
			Length = Vec.LengthSq();
			m_Rot.y = atan2(Vec.x, Vec.z);
			m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed6;
		}
	}

	if (m_BossEnemy.isAnimationEnd())
	{
		m_Check = false;
		m_State = eState_Ikari;
	}
}

void BossEnemy::Damage()
{
	if (m_Hp > 50)
	{
		m_State = eState_Hakken;
	}
	
	if (m_Hp <= 50 && m_Check == false)
	{
		m_State = eState_Ikari;
	}

	if (m_Check == true)
	{
		m_State = eState_Attack3;
	}
}

void BossEnemy::Down()
{
	m_BossEnemy.ChangeAnimation(8);
	if (m_BossEnemy.isAnimationEnd())
	{
		m_Kill = true;
		Base::Add(new Key2(m_Pos + CVector3D(0, 1, 0), CVector3D(0, 0, 0)));
		Base* H = Base::FindObject(eId_HitCollision2);
		H->Count = 0;
	}
}

void BossEnemy::Render()
{
	m_BossEnemy.SetPos(m_Pos);
	m_BossEnemy.SetRot(m_Rot);
	m_BossEnemy.SetScale(0.015f, 0.015f, 0.015f);
	m_BossEnemy.Render();

	View_Matrix = m_BossEnemy.GetFrameMatrix(36);
	View_Pos = View_Matrix * CVector4D(0, 0, 0, 1);

	/*
	Utility::DrawLine(View_Pos, View_Pos + View_Dir * View_Length, CVector4D(0, 0, 0, 1));
	//Y軸の範囲
	Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationY(View_Ang_Y) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
	Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationY(-View_Ang_Y) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
	//X軸の範囲
	Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationX(View_Ang_X) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
	Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationX(-View_Ang_X) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
	*/
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(1, 0, 0, 1));
}

void BossEnemy::Collision(Base* B)
{
	switch (B->GetTypeId())
	{
	case eId_BossEnemy:
		CollisionCharctor(B);
		break;
	case eId_PlayerAttack:
		if (CollisionCapsule(this, B))
		{
			B->m_Kill = true;
			m_Hp -= 1;
			if (m_Hp > 0)
			{
				m_State = eState_Damage;
			}

			if (m_Hp == 0)
			{
				m_State = eState_Down;
			}
		}
		break;
	case eId_TutorialField:
		//フィールドとの衝突
		CollisionField(B->GetModel());
		break;
	}
}