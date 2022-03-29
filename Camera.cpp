#include "Camera.h"
#include "Player.h"
#include "HitCollision.h"
#include "../Screen/Title.h"

Camera::Camera() : Base(eId_Camera)
{
}

void Camera::Update()
{
	if (ClearCollision::Switch::m_CameraSwitch == false && Title::Screen::m_Title == false)
//	if (ClearCollision::Switch::m_CameraSwitch == false && Title::Screen::m_Title == true)
	{
		Base* P = Base::FindObject(eId_Player);
		m_Pos = P->m_Pos;
		m_Rot = P->m_Rot;
		Player_Matrix = CMatrix::MTranselate(m_Pos);
		if (HOLD(CInput::eMouseR) && Player::Mode::m_Squat == false && Player::Mode::m_Prone == false)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.7, 0.5, -1.37));
			Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.5, -1.37));
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.4, 0.5, -1.37));
		}
		else if (HOLD(CInput::eMouseR) && Player::Mode::m_Squat == true)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.7, 0.5, -1.37));
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.5, -1.37));
			Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.05, -1.37));
		}
		else if (HOLD(CInput::eMouseR) && Player::Mode::m_Prone == true)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.7, 0.5, -1.37));
			//Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.5, -1.37));
			Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.4, -0.5, -1));
		}
		else if (Player::Mode::m_Squat == false && Player::Mode::m_Prone == false)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1.15, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.5, -2));
		}
		else if (Player::Mode::m_Squat == true && Player::Mode::m_Prone == false)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1.15, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.05, -2));
			//Move_Camera = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 0.05, -2));
			//Camera_Matrix = Camera_Matrix * 0.8 + Move_Camera * 0.2;
		}
		else if (Player::Mode::m_Squat == false && Player::Mode::m_Prone == true)
		{
			//支点の行列
			Parent_Matrix = Player_Matrix * CMatrix::MTranselate(CVector3D(0, 1.15, 0)) * CMatrix::MRotation(m_Rot);
			//カメラの行列
			if (Player::Mode::m_Prone == true || Player::Roll::m_RollLeft == true || Player::Roll::m_RollRight == true)
			{
				Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, -0.5, -2));
			}
			else
			{
				Move_Camera = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, -0.5, -2));
				Camera_Matrix = Camera_Matrix * 0.8 + Move_Camera * 0.2;
			}

		}
		CCamera::GetCurrent()->SetTranseRot(Camera_Matrix);
	}
	
	if (ClearCollision::Switch::m_CameraSwitch == true)
	{
		m_Rot = CVector3D(0, 0, 0);
		m_Pos = CVector3D(-46.5, 8.5, -56);
		Parent_Matrix = CMatrix::MTranselate(CVector3D(m_Pos)) * CMatrix::MRotation(m_Rot);
		Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(-0.5, 1, 10));
		CCamera::GetCurrent()->SetTranseRot(Camera_Matrix);
	}

	if (Title::Screen::m_Title == true)
	//if (Title::Screen::m_Title == false)
	{
		m_Rot = CVector3D(0, -90, 0);
		m_Pos = CVector3D(1, 0.5, 1);
		Parent_Matrix = CMatrix::MTranselate(CVector3D(m_Pos)) * CMatrix::MRotation(m_Rot);
		Camera_Matrix = Parent_Matrix * CMatrix::MTranselate(CVector3D(0, 1, 0));
		CCamera::GetCurrent()->SetTranseRot(Camera_Matrix);
	}
}

void Camera::Render()
{
}