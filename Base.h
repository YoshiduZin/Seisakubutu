#pragma once
#include "../stdafx.h"
#include "../GID.h"
#define GRVITY (0.1f/20);

class Base
{
private:
	//�^�C�vID
	int m_TypeId;
	//
	static std::list<Base*> m_List;

public:
	//3D���W
	CVector3D m_Pos;
	//�ߋ��̍��W
	CVector3D m_Pos_Old;
	//��]�l
	CVector3D m_Rot;
	//�ړ���
	CVector3D m_Vec;
	CVector3D V;
	CVector3D Dir;
	CVector3D LineS;
	CVector3D LineE;
	CVector3D Center;
	CVector3D* Axis;
	COBB A;
	//���a
	float m_Rad;
	float L;
	float S;
	float* Length;
	int Count;
	int m_Hit_Id;
	int m_Hp_Now;
	/* �L�[�������Ă��邩 */
	int Key1_Count;
	int Key2_Count;
	//�폜�t���O
	bool m_Kill;
	bool m_Death = false;
	/* �{�X�p�̊֐� */
	//�U���t���O
	bool m_Attack1 = false;
	bool m_Attack2 = false;
	bool m_Syutugen = false;

public:
	Base(int Type_Id);
	virtual ~Base();
	//�^�C�v��ʂ̏���
	int GetTypeId()
	{
		return m_TypeId;
	}
	void SetPos(const CVector3D& Pos)
	{
		m_Pos = Pos;
	}
	CVector3D GetPos()
	{
		return m_Pos;
	}
	void SetRot(const CVector3D& Rot)
	{
		m_Rot = Rot;
	}
	CVector3D GetRot()
	{
		return m_Rot;
	}
	virtual CModel* GetModel()
	{
		return nullptr;
	}
	virtual void Update();
	virtual void Render();
	virtual void Draw();
	virtual void Collision(Base* B);
	//�L�����N�^�[�̏Փˌ���
	void CollisionCharctor(Base* B);
	//�t�B�[���h�̏Փˌ���
	void CollisionField(CModel* M);
	//�J�v�Z���̏Փˌ���
	static bool CollisionCapsule(Base* B1, Base* B2);
	//�l�p�̏Փˌ���
	static bool CollisionOBBShpere(Base* B1, Base* B2);
	//�S�ẴI�u�W�F�N�g�̍폜
	static void KillALL();
	//�S�ẴI�u�W�F�N�g�̍X�V
	static void UpdateAll();
	//�S�ẴI�u�W�F�N�g�̕`��(3D���f��)
	static void RenderAll();
	//�S�ẴI�u�W�F�N�g�̕`��(UI)
	static void DrawAll();
	//�S�ẴI�u�W�F�N�g���m�̏Փˌ���
	static void CollisionAll();
	//�S�ẴI�u�W�F�N�g�̍폜�`�F�b�N
	static void KillCheck();
	//�I�u�W�F�N�g��ǉ�
	static void Add(Base* B);
	//�I�u�W�F�N�g�̌���
	static Base* FindObject(int Type_Id);
};