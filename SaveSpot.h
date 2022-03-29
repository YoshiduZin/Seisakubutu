#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class SaveSpot1 : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_Idle,	//�Z�[�u�X�|�b�g�̏������
	};

	//��Ԃ̕ϐ�
	int m_State;

	void Idle();

public:
	/* CModelObj */
	CModelObj m_SaveSpot1;
	int m_Count;

public:
	SaveSpot1(const CVector3D& Pos, const CVector3D& Rot);
	void Update();
	void Render();
	void Collision(Base* B);
};