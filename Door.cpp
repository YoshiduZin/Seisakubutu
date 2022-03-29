#include "Door.h"
#include "Player.h"
#include "BossEnemy.h"
#include "../Screen/Title.h"
#include "HitCollision.h"

/* Door1 */
bool Door1::Mode::m_OpenDoor1 = false;

/* Door2 */
bool Door2::Mode::m_OpenDoor2 = false;

bool Door1::Switch::Door_1 = false;
bool Door2::Switch::Door_2 = false;

Door1::Door1(const CVector3D& Pos, const CVector3D& Rot) : Base(eId_Door1)
{
	m_Door1 = COPY_RESOURCE("Door", CModelObj);
	m_Pos = Pos;
	m_Rot = Rot;
	m_Rad = 1.0f;

	m_State = eState_Idle;
}

void Door1::Update()
{
	LineS = m_Pos + CVector3D(0, 0.8, 0.6);
	LineE = m_Pos + CVector3D(0, 1.2, 0.6);

	if (Door1::Mode::m_OpenDoor1 == false)
	{
		A = COBB(CVector3D(m_Pos + CVector3D(0, 0, 0.65)), CVector3D(1, 0, 0), CVector3D(0, 1, 0), CVector3D(0, 0, 1), CVector3D(0.01, 2.8, 0.6));
	}

	switch (m_State)
	{
	case eState_Idle:
		Idle();
		break;
	case eState_Open:
		Open();
		break;
	case eState_Close:
		Close();
		break;
	}
}

void Door1::Idle()
{
	
}

void Door1::Open()
{
	m_Rot.y -= DtoR(5);
	if (m_Rot.y <= DtoR(-180))
	{
		
		m_Rot.y = DtoR(-180);
	}
}

void Door1::Close()
{
}

void Door1::Render()
{
	if (Title::Screen::m_Title == false)
	{
		m_Door1.SetPos(m_Pos);
		m_Door1.SetRot(m_Rot);
		m_Door1.SetScale(1.5, 1.4, 1);
		m_Door1.Render();
	}
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
	//if (Door1::Mode::m_OpenDoor1 == false)
	//{
	//	A.Draw(CVector4D(1, 0, 0, 1));
	//}
}

void Door1::Collision(Base* B)
{
	switch (B->GetTypeId())
	{
		
	case eId_Player:
		if (CollisionCapsule(this, B))
		{
			if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Door1::Mode::m_OpenDoor1 == false)
			{
				Base* P = Base::FindObject(eId_Player);
				if (Player::GetKey::m_Key1 == true || P->Key1_Count == 1)
				{
					if (Switch::Door_1 == false)
					{
						
					}
					Switch::Door_1 = true;
					Door1::Mode::m_OpenDoor1 = true;
					m_State = eState_Open;
				}
			}
		}
		break;
	}
}

Door2::Door2(const CVector3D& Pos, const CVector3D& Rot) : Base(eId_Door2)
{
	m_Door2 = COPY_RESOURCE("Door", CModelObj);
	m_Pos = Pos;
	m_Rot = Rot;
	m_Rad = 1.0f;

	m_State = eState_Idle;
}

void Door2::Update()
{
	LineS = m_Pos + CVector3D(-0.6, 0.8, 0);
	LineE = m_Pos + CVector3D(-0.6, 1.2, 0);

	if (Door2::Mode::m_OpenDoor2 == false)
	{
		A = COBB(CVector3D(m_Pos + CVector3D(-0.65, 0, 0)), CVector3D(1, 0, 0), CVector3D(0, 1, 0), CVector3D(0, 0, 1), CVector3D(0.6, 2.8, 0.01));
	}

	switch (m_State)
	{
	case eState_Idle:
		Idle();
		break;
	case eState_Open:
		Open();
		break;
	case eState_Close:
		Close();
		break;
	}
}

void Door2::Idle()
{
}

void Door2::Open()
{
	m_Rot.y -= DtoR(5);
	if (m_Rot.y <= DtoR(90))
	{
		m_Rot.y = DtoR(90);
	}
}

void Door2::Close()
{
	/*
	m_Rot.y += DtoR(5);
	if (m_Rot.y >= DtoR(-90))
	{

		m_Rot.y = DtoR(-90);
	}
	*/
}

void Door2::Render()
{
	if (Title::Screen::m_Title == false)
	{
		m_Door2.SetPos(m_Pos);
		m_Door2.SetRot(m_Rot);
		m_Door2.SetScale(1.5, 1.4, 1);
		m_Door2.Render();
	}
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));
	//if (Door2::Mode::m_OpenDoor2 == false)
	//{
	//	A.Draw(CVector4D(1, 0, 0, 1));
	//}
}

void Door2::Collision(Base* B)
{
	switch (B->GetTypeId())
	{

	case eId_Player:
		if (CollisionCapsule(this, B))
		{
			if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Door2::Mode::m_OpenDoor2 == false)
			{
				Base* P = Base::FindObject(eId_Player);
				if (Player::GetKey::m_Key2 == true && P->Key2_Count == 1);
				{
					if (Switch::Door_2 == false)
					{
						Base::Add(new ClearCollision(CVector3D(-47.55, 9, -40.1)));
					}
					Switch::Door_2 = true;
					Door2::Mode::m_OpenDoor2 = true;
					m_State = eState_Open;
				}
			}

			/*
			else if (CInput::GetState(0, CInput::ePush, CInput::eGet) && Door2::Mode::m_OpenDoor2 == true)
			{
				Door2::Mode::m_OpenDoor2 = false;
				m_State = eState_Close;
			}
			*/
		}
		break;
	}
}