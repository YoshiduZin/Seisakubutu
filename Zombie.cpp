#include "Zombie.h"
#include "EnemyKill.h"
#include "AmmoBox.h"
#include "Key.h"
#include "../Screen/Title.h"

Zombie::Zombie(const CVector3D& P) : Base(eId_Zombie)
{
	m_Pos = P;
	m_Zombie = COPY_RESOURCE("Zombie", CModelA3M);
	m_Rad = 0.4f;
	m_Hp = 10;
	m_Attack = false;

	/* 未発見時のカウント */
	m_Count1 = 0;
	m_Count2 = 0;

	m_Count3 = 0;

	View_Ang_Y = DtoR(45);
	//View_Ang_X = DtoR(30);
	View_Length = 10;

	if (Title::Screen::m_Title == false)
	{
		//はじめは通常状態へ
		m_State = eState_Idle;
	}
}

Zombie::~Zombie()
{

}

void Zombie::Update()
{
	//状態の切り替え
	switch (m_State)
	{
	case eState_Idle:
		Idle();	//通常状態へ
		break;
	case eState_Mihakken:
		Mihakken();	//未発見状態へ
		break;
	case eState_Hakken:
		Hakken();	//発見状態へ
		break;
	case eState_Attack1:
		Attack1();	//攻撃状態へ
		break;
	case eState_Attack2:
		Attack2();	//攻撃状態へ
		break;
	case eState_Damage:
		Damage();	//ダメージ状態
		break;
	case eState_Down:
		Down();	//死亡状態へ
		break;
	}

	LineS = m_Pos + CVector3D(0, 0.5, 0);
	LineE = m_Pos + CVector3D(0, 1.1, 0);

	m_Zombie.UpdateAnimation();

	m_Vec.y -= GRVITY;
	m_Pos += m_Vec;

	View_Dir = CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y));
}

void Zombie::Idle()
{
	if (Base* Player = Base::FindObject(eId_Player))
	{
		/* ゾンビからプレイヤーへの距離 */
		LVec = Player->m_Pos - m_Pos;
		Length = LVec.Length();

		/* ボスからプレイヤーへの方向と角度 */
		AVec = LVec / LVec.Length();
		D = CVector3D::Dot(View_Dir, AVec);
		if (D >= 1)
			D = 1;
		Ang = acos(D);

		if (Ang <= View_Ang_Y && Length <= View_Length)
		{
			//発見状態へ
			m_State = eState_Hakken;
		}
		else
		{
			//未発見状態へ
			m_State = eState_Mihakken;
		}
	}
}

void Zombie::Mihakken()
{
	if (Base* Player = Base::FindObject(eId_Player))
	{
		/* 敵からプレイヤーへの距離 */
		LVec = Player->m_Pos - m_Pos;
		Length = LVec.Length();

		/* 敵からプレイヤーへの方向と角度 */
		AVec = LVec / LVec.Length();
		D = CVector3D::Dot(View_Dir, AVec);
		if (D >= 1)
			D = 1;
		Ang = acos(D);

		if (Ang <= View_Ang_Y && Length <= View_Length)
		{
			//発見状態へ
			m_State = eState_Hakken;
		}
		else
		{
			if (m_Count1 < 1000)
			{
				m_Count2 = 0;
				m_Rot.y = atan2(LVec.x, LVec.z);
				m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed;
				m_Zombie.ChangeAnimation(2);
				m_Count1++;
			}
			
			if (m_Count1 == 1000)
			{
				if (m_Count2 < 200)
				{
					m_Zombie.ChangeAnimation(0);
					m_Count2++;
				}

				if (m_Count2 == 200)
				{
					m_Count1 = 0;
				}
			}

		}
	}
}

void Zombie::Hakken()
{
	if (m_Hakken == false)
	{
		m_Zombie.ChangeAnimation(3);
		if (m_Zombie.isAnimationEnd())
			m_Hakken = true;
	}

	if (m_Hakken == true)
	{
		if (Base* Player = Base::FindObject(eId_Player))
		{
			if (TargetIsPlyer)
			{
				Vec = Player->GetPos() - m_Pos;
				Length = Vec.LengthSq();
				if (Length <= 0.65)
				{
					if (rand() % 100 < 50)
					{
						//攻撃状態(パターン1)へ
						m_State = eState_Attack1;
					}

					else if (rand() % 100 < 20)
					{
						//攻撃状態(パターン2)へ
						m_State = eState_Attack2;
					}
				}
			}

			else
			{
				Vec = Target - m_Pos;
				Length = Vec.LengthSq();
			}

			float y = atan2(Vec.x, Vec.z);
			m_Rot.y += Utility::NormalizeAngle(y - m_Rot.y) * 0.1f;
			m_Zombie.ChangeAnimation(5);

			if (Length > 0.65 && TargetMoveTime++ < 180)
			{
				m_Pos += CVector3D(sin(m_Rot.y), 0, cos(m_Rot.y)) * Move_Speed2;
			}

			else 
			{
				UpdateTargetPoint();
			}
		}
	}
}

void Zombie::UpdateTargetPoint()
{
	if (Base* Player = Base::FindObject(eId_Player)) 
	{
		CMatrix m;
		m.LookAt(Player->GetPos(), m_Pos, CVector3D::up);
		int r = rand() % 100;

		if (r < 20) 
		{
			//右
			Target = m * CVector4D(5, 0, 0, 1);
			TargetIsPlyer = false;
		}

		else if (r < 40)
		{
			//左
			Target = m * CVector4D(-5, 0, 0, 1);
			TargetIsPlyer = false;
		}

		else 
		{
			TargetIsPlyer = true;
		}

	}
	TargetMoveTime = rand() % 60;
}

void Zombie::Attack1()
{
	m_Zombie.ChangeAnimation(6);
	if (m_Zombie.GetAnimationFrame() > 30 && m_Zombie.GetAnimationFrame() < 45)
		m_Attack1 = true;
	else
		m_Attack1 = false;
	if (m_Zombie.isAnimationEnd())
	{
		m_Hit_Id += 1;
		//発見状態へ
		m_State = eState_Hakken;
		m_Attack1 = false;
	}
}

void Zombie::Attack2()
{
	m_Zombie.ChangeAnimation(7);
	if (m_Zombie.GetAnimationFrame() > 39 && m_Zombie.GetAnimationFrame() < 59)
		m_Attack2 = true;
	else
		m_Attack2 = false;
	if (m_Zombie.isAnimationEnd())
	{
		m_Hit_Id += 1;
		//発見状態へ
		m_State = eState_Hakken;
		m_Attack2 = false;
	}
}

void Zombie::Damage()
{
	//発見状態へ
	m_State = eState_Hakken;
}

void Zombie::Down()
{
	m_Zombie.ChangeAnimation(9);
	if (m_Zombie.isAnimationEnd())
	{
		m_Kill = true;
		EnemyKill::m_Score += 1;
		if (EnemyKill::m_Score < 30)
		{
			if (rand() % 100 < 50 )
			{
				Base::Add(new AmmoBox(m_Pos));
			}
		}

		if (EnemyKill::m_Score < 30)
		{
			
			if (EnemyKill::m_Score == 10)
			{
				for (int I = 0; I < 10; I++)
				{
					float Range = 5;
					CVector3D Pos(Utility::Rand(-Range, Range), 4, Utility::Rand(-Range, Range));
					Base::Add(new Zombie(CVector3D(Pos + CVector3D(20, 0, 45))));
				}
			}

			if (EnemyKill::m_Score == 20)
			{
				for (int I = 0; I < 10; I++)
				{
					float Range = 5;
					CVector3D Pos(Utility::Rand(-Range, Range), 4, Utility::Rand(-Range, Range));
					Base::Add(new Zombie(CVector3D(Pos + CVector3D(-20, 0, 45))));
				}
			}
		}
		if (EnemyKill::m_Score == 30)
		{
			Base::Add(new Key1(m_Pos + CVector3D(0, 1, 0), CVector3D(0, 0, 0)));
		}
	}


}

void Zombie::Render()
{
	if (Title::Screen::m_Title == false)
	{
		CLight::SetLighting(false);

		m_Zombie.SetPos(m_Pos);
		m_Zombie.SetRot(m_Rot);
		m_Zombie.SetScale(0.01f, 0.01f, 0.01f);
		m_Zombie.Render();

		if (m_Death == false)
		{
			//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(1, 0, 0, 1));
			View_Matrix = m_Zombie.GetFrameMatrix(7);
			View_Pos = View_Matrix * CVector4D(0, 0, 0, 1);
			/*
			Utility::DrawLine(View_Pos, View_Pos + View_Dir * View_Length, CVector4D(0, 0, 0, 1));
			Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationY(View_Ang_Y) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
			Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationY(-View_Ang_Y) * View_Dir * View_Length, CVector4D(0, 0, 0, 1));
			*/
			//Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationX(View_Ang_X) * Dir * View_Length, CVector4D(0, 0, 0, 1));
			//Utility::DrawLine(View_Pos, View_Pos + CMatrix::MRotationX(-View_Ang_X) * Dir * View_Length, CVector4D(0, 0, 0, 1));
		}

		CLight::SetLighting(true);
	}
}

void Zombie::Collision(Base* B)
{
	switch (B->GetTypeId())
	{
		if (m_Death == false)
		{
		case eId_Zombie:
			CollisionCharctor(B);
			break;

		case eId_PlayerAttack:
			if (CollisionCapsule(this, B))
			{
				B->m_Kill = true;
				m_Hp -= 1;
				if (m_Hp > 0)
				{
					m_Hakken = true;
					//ダメージ状態へ
					m_State = eState_Damage;
				}

				if (m_Hp == 0)
				{
					m_Death = true;
					//死亡状態へ
					m_State = eState_Down;
				}
			}
			break;
		}


	case eId_TutorialField:
		//フィールドとの衝突
		CollisionField(B->GetModel());
		break;
	}
}