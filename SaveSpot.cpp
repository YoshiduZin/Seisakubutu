#include "SaveSpot.h"
#include "Player.h"
#include "../Screen/Title.h"
#include "../Screen/Pause.h"
#include "../Data/SaveData/Save.h"
#include "../Game/HitCollision.h"
#include "../Game/EnemyKill.h"

SaveSpot1::SaveSpot1(const CVector3D& Pos, const CVector3D& Rot) : Base(eId_SaveSpot)
{
	m_SaveSpot1 = COPY_RESOURCE("Save", CModelObj);
	m_Pos = Pos;
	m_Rot = Rot;
	m_Rad = 0.5f;

	m_State = eState_Idle;
}

void SaveSpot1::Update()
{
	LineS = m_Pos + CVector3D(1.5, 0.5, 0);
	LineE = m_Pos + CVector3D(1.5, 2, 0);

	A = COBB(CVector3D(m_Pos + CVector3D(0.3, 0, 0)), CVector3D(1, 0, 0), CVector3D(0, 1, 0), CVector3D(0, 0, 1), CVector3D(0.8, 2.5, 0.5));

	switch (m_State)
	{
	case eState_Idle:
		Idle();
		break;
	}
}

void SaveSpot1::Idle()
{
}

void SaveSpot1::Render()
{
	if (Title::Screen::m_Title == false)
	{
		m_SaveSpot1.SetPos(m_Pos);
		m_SaveSpot1.SetRot(m_Rot);
		m_SaveSpot1.SetScale(0.5, 0.5, 0.5);
		m_SaveSpot1.Render();
	}
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
	//A.Draw(CVector4D(1, 0, 0, 1));
}

void SaveSpot1::Collision(Base* B)
{
	switch (B->GetTypeId())
	{

	case eId_Player:
		if (CollisionCapsule(this, B))
		{
			Base* H = Base::FindObject(eId_HitCollision2);
			if (H->Count == 0)
			{
				if (Player::Save::m_Pause == false)
					Player::Hyouzi::m_Hyouzi1 = true;

				if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Player::Save::m_Pause == false)
				{
					Pause::Check::PauseCheck = true;
					Player::Hyouzi::m_Hyouzi1 = false;
					Player::Save::m_Pause = true;
					Base::Add(new Pause);
					Save::Writing();
				}

				if (CInput::GetState(0, CInput::ePush, CInput::ePause) && Player::Save::m_Pause == true)
				{
					Base* B = Base::FindObject(eId_Pause);
					B->m_Kill = true;
					Player::Save::m_Pause = false;
					Pause::Check::PauseCheck = false;
				}
			}

		}
		else
		{
			Player::Hyouzi::m_Hyouzi1 = false;
		}
		break;
	}
}