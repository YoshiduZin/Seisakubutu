#include "HitCollision.h"
#include "Zombie.h"
#include "BossEnemy.h"
#include "EnemyKill.h"

bool ClearCollision::Hit::m_CollisionHit = false;
bool ClearCollision::Switch::m_CameraSwitch = false;

bool EnemyCollision::Hit::m_CollisionHit = false;
bool EnemyCollision::Switch::m_EnemySwitch = false;

bool BossCollision::Hit::m_CollisionHit = false;
bool BossCollision::Switch::m_BossSwitch = false;

ClearCollision::ClearCollision(const CVector3D& Pos) : Base(eId_Hit2)
{
	m_Pos = Pos;
	m_Rad = 0.1f;

	m_State = eState_NoHit;
}

void ClearCollision::Update()
{
	LineS = m_Pos + CVector3D(2.3, 0.1, 0);
	LineE = m_Pos + CVector3D(-2.3, 0.1, 0);


	switch (m_State)
	{
	case eState_NoHit:
		NoHit();
		break;
	case eState_Hit:
		Hit();
		break;
	case eState_End:
		End();
		break;
	}
}

void ClearCollision::NoHit()
{
	if (Hit::m_CollisionHit == true)
	{
		m_State = eState_Hit;
	}
}

void ClearCollision::Hit()
{
	if (Hit::m_CollisionHit == true)
	{
		Switch::m_CameraSwitch = true;
	}
}

void ClearCollision::End()
{

}

void ClearCollision::Render()
{
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void ClearCollision::Collision(Base* B)
{
}

EnemyCollision::EnemyCollision(const CVector3D& Pos) : Base(eId_HitCollision1)
{
	m_Pos = Pos;
	m_Rad = 0.1f;
	m_Count = 0;
	Count = 0;

	m_State = eState_NoHit;
}

void EnemyCollision::Update()
{
	LineS = m_Pos + CVector3D(0, 0.1, 2.3);
	LineE = m_Pos + CVector3D(0, 0.1, -2.3);


	switch (m_State)
	{
	case eState_NoHit:
		NoHit();
		break;
	case eState_Hit:
		Hit();
		break;
	case eState_End:
		End();
		break;
	}
}

void EnemyCollision::NoHit()
{
	if (Hit::m_CollisionHit == true)
	{
		m_State = eState_Hit;
	}
}

void EnemyCollision::Hit()
{
	Base* P = Base::FindObject(eId_Player);
	if (Hit::m_CollisionHit == true && P->Key1_Count == 0 && EnemyKill::m_Score == 0)
	{
		Switch::m_EnemySwitch = true;
		if (Switch::m_EnemySwitch == true)
		{
			if (m_Count == 0)
			{
				for (int I = 0; I < 10; I++)
				{
					float Range = 5;
					CVector3D Pos(Utility::Rand(-Range, Range), 4, Utility::Rand(-Range, Range));
					Base::Add(new Zombie(CVector3D(Pos + CVector3D(-20, 0, 45))));
				}
				m_Count++;
			}
			else
			{
				m_State = eState_End;
			}
		}
	}
}

void EnemyCollision::End()
{
	Switch::m_EnemySwitch = false;
}

void EnemyCollision::Render()
{
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void EnemyCollision::Collision(Base* B)
{
}

BossCollision::BossCollision(const CVector3D& Pos) : Base(eId_HitCollision2)
{
	m_Pos = Pos;
	m_Rad = 0.1f;
	m_Count = 0;
	Count = 0;

	m_State = eState_NoHit;
}

void BossCollision::Update()
{
	LineS = m_Pos + CVector3D(2.3, 0.1, 0);
	LineE = m_Pos + CVector3D(-2.3, 0.1, 0);


	switch (m_State)
	{
	case eState_NoHit:
		NoHit();
		break;
	case eState_Hit:
		Hit();
		break;
	case eState_End:
		End();
		break;
	}
}

void BossCollision::NoHit()
{
	if (Hit::m_CollisionHit == true)
	{
		m_State = eState_Hit;
	}
}

void BossCollision::Hit()
{
	Base* P = Base::FindObject(eId_Player);
	if (Hit::m_CollisionHit == true && P->Key2_Count == 0)
	{
		Switch::m_BossSwitch = true;
		if (Switch::m_BossSwitch == true)
		{
			if (m_Count == 0)
			{
				Count = 1;
				Base::Add(new BossEnemy(CVector3D(-40, 1, -20)));
				m_Count++;
			}
			else
			{
				m_State = eState_End;
			}
		}
	}
}

void BossCollision::End()
{
	Switch::m_BossSwitch = false;
}

void BossCollision::Render()
{
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
}

void BossCollision::Collision(Base* B)
{
}