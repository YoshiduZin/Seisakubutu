#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class Zombie : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_Idle,		//�ʏ���
		eState_Mihakken,	//���������
		eState_Hakken,		//�������
		eState_Attack1,		//�U�����(�p�^�[��1)
		eState_Attack2,		//�U�����(�p�^�[��2)
		eState_Damage,		//�_���[�W���
		eState_Down,		//���S���

	};

	//��Ԃ̕ϐ�
	int m_State;

	void Idle();
	void Mihakken();
	void Hakken();
	void UpdateTargetPoint();
	void Attack1();
	void Attack2();
	void Damage();
	void Down();

public:
	/* CModelA3M */
	//�I���f���̃I�u�W�F�N�g
	CModelA3M m_Zombie;

	/* CMatrix */
	CMatrix View_Matrix;

	/* CVector3D */
	CVector3D LVec;
	CVector3D AVec;
	CVector3D View_Pos;
	CVector3D View_Dir;

	CVector3D Vec;
	CVector3D Vec_Z;

	CVector3D Target;
	bool	TargetIsPlyer;
	int		 TargetMoveTime;

	/* float , const float */
	float Length = 0;
	float Length_Z = 0;
	float View_Ang_Y;
	float View_Ang_X;
	float View_Length;
	float D = 0;
	float Ang;
	const float Move_Speed = 0.02f;
	const float Move_Speed2 = 0.1f;

	/* int */
	//�̗�
	int m_Hp;
	//�폜�֐�
	int m_Delete;

	int m_Count1;
	int m_Count2;
	int m_Count3;

	/* bool */
	//�U��
	bool m_Attack;
	bool m_Hakken = false;

public:
	//�R���X�g���N�^
	Zombie(const CVector3D& Pos);
	~Zombie();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�����蔻��̌���
	void Collision(Base* B);
};