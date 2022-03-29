#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"

class BossEnemy : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_Idle,	//�ʏ���
		eState_Mihakken,//���������
		eState_Hakken,	//�������
		eState_Ikari,	//�{����
		eState_Attack1,	//��U�����
		eState_Attack2, //���U�����
		eState_Attack3,	//�W�����v�U�����
		eState_Damage,	//�_���[�W���
		eState_Down,	//���S���
	};

	//��Ԃ̕ϐ�
	int m_State;

	void Idle();
	void Mihakken();
	void Hakken();
	void Ikari();
	void Attack1();
	void Attack2();
	void Attack3();
	void Damage();
	void Down();

	int Point = 1;

public:
	/* CModelA3M */
	CModelA3M m_BossEnemy;

	/* CMatrix */
	CMatrix View_Matrix;

	/* CVector3D */
	//�����O�̕ϐ�
	//�����̃x�N�g��
	CVector3D LVec;
	//�p�x�̃x�N�g��
	CVector3D AVec;
	//�ڐ��̏ꏊ
	CVector3D View_Pos;
	//�ڐ��̊p�x
	CVector3D View_Dir;
	//������̕ϐ�
	CVector3D Vec;

	/* float , const float */
	//����
	float Length = 0;
	//Y���̊p�x
	float View_Ang_Y;
	//X���̊p�x
	float View_Ang_X;
	//�ڐ�����̋���
	float View_Length;
	float D = 0;
	float Ang;
	//�X�s�[�h�Ǘ�
	
	//��������
	const float Move_Speed = 0.05f;
	//������
	const float Move_Speed2 = 0.1f;
	//�{�莞
	const float Move_Speed3 = 0.15f;
	//�_�b�V��
	const float Move_Speed4 = 0.2f;
	//�W�����v(1�p�^�[����)
	const float Move_Speed5 = 0.25f;
	//�W�����v(2�p�^�[����)
	const float Move_Speed6 = 0.35f;

	/* int */
	//�̗�
	int m_Hp;

	/* bool */
	//���[�h�Ǘ�
	struct Mode
	{
		static bool m_Hakken;	//����
		static bool m_Ikari;	//�{��
		static bool m_Jump;		//�W�����v
	};

	bool m_Check;

	static const int Mode_Max = 3;

public:
	//�R���X�g���N�^
	BossEnemy(const CVector3D& Pos);
	//�X�V
	void Update();
	//�`��
	void Render();
	//�����蔻��̌���
	void Collision(Base* B);
};