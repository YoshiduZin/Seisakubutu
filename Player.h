#pragma once
#include "../stdafx.h"
#include "../Base/Base.h"
#include "PlayerWepon.h"
#include "PlayerAttack.h"

class Player : public Base
{
private:
	//�e��Ԗ�
	enum
	{
		eState_Idle,	//�ʏ���
		eState_Squat,	//���Ⴊ�ݏ��
		eState_Prone,	//�������
		eState_Rotate,	//��]���(��������)
		eState_Attack,	//�U�����
		eState_Damage,	//�_���[�W���
		eState_Down,	//���S���
		eState_Pause,	//�|�[�Y���
		eState_Event	//�C�x���g���
	};

	//��Ԃ̕ϐ�
	int m_State;

	void Idle();
	void Squat();
	void Prone();
	void Rotate();
	void Attack();
	void Damage();
	void Down();
	void Menu();
	void Event();

public:
	/* CModelA3M */
	//���f���̃I�u�W�F�N�g
	CModelA3M m_Model;

	/* CMatrix */
	//�v���C���[�̍s��
	CMatrix Player_Matrix;
	//��]�s��
	CMatrix Rot_Matrix;
	//�v���C���[�̎��_(�{�[���ɑg�ݍ��ݗp)
	CMatrix View_Matrix;

	/* CVector3D */
	//���͕����x�N�g��
	CVector3D Key_Dir;
	//�v���C���[�̈ړ������̊֐�
	CVector3D Dir;
	//�ː�
	CVector3D Wepon_Pos;
	CVector3D Vec;
	//���_�n
	CVector3D LVec;
	CVector3D AVec;
	CVector3D View_Pos;
	CVector3D View_Dir;

	/* CVector2D */
	//�}�E�X�x�N�g��
	CVector2D Mouse_Vec;

	/* CImage */
	CImage m_Life[11];
	CImage m_Img[3];

	/* const float */
	//�ʏ��Ԃ̈ړ���
	const float Move_Speed = 0.1f;
	//�ʏ��Ԃ̈ړ���(������\����)
	const float Move_Speed2 = 0.045f;
	//���Ⴊ�ݏ�Ԃ̈ړ���
	const float Move_Speed3 = 0.045f;
	//���Ⴊ�ݏ󋵂̈ړ���(������\����)
	const float Move_Speed4 = 0.02f;
	//������Ԃ̈ړ���
	const float Move_Speed5 = 0.02f;
	//������Ԃ̈ړ���(���E�ɓ]����)
	const float Move_Roll = 0.045f;
	/* float */
	//�ő�̗�
	float m_Hp_Max;
	//���݂̗̑�
	//float m_Hp_Now;
	float Length = 0;
	float D = 0;
	float View_Length;
	float View_Ang;
	float Ang;

	/* int */
	//�����[�h�֐�
	int m_Reload;
	//�ˌ��֐�
	int m_Shot;
	//�e�̒e��
	int Bullet_Count;
	//�e�e�̊Ԋu
	int Bullet_Interval;
	//�e�e�̕�[
	int Bullet_Refill;
	//�폜�J�E���g
	int Kill_Count;

	int m_Count;

	int m_HitCount;

	struct Hyouzi
	{
		static bool m_Hyouzi1;
		static bool m_Hyouzi2;
		static bool m_Hyouzi3;
	};

	/* �G���A�̌� */
	struct GetKey
	{
		static bool m_Key1;
		static bool m_Key2;
	};
	static const int Key_Max = 2;
	
	/* �̐��ω� */
	struct Mode
	{
		//���Ⴊ��
		static bool m_Squat;
		//����
		static bool m_Prone;
	};

	struct Roll
	{
		//��	
		static bool m_RollLeft;
		//�E
		static bool m_RollRight;
	};
	
	struct Switch
	{
		//�Q�[���N���A
		static bool m_GameClear;
		//�Q�[���I�[�o�[
		static bool m_GameOver;
	};

	bool m_Button = false;

	struct Save
	{
		static bool m_Pause;
	};

	/* �N���X�g�p */
	//PlayerWepon�N���X���g�p
	PlayerWepon m_Wepon_Class;

public:
	
	//�R���X�g���N�^
	Player(const CVector3D& Pos);
	~Player();
	//�X�V
	void Update();
	//�`��
	void Render();
	//�`��(�̗͗p)
	void Draw();
	//�����蔻��̌���
	void Collision(Base* B);
};
