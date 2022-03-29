#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "Save.h"
#include "../GameProject/Game/Player.h"
#include "../GameProject/Game/BulletNumber.h"
#include "../GameProject/Game/RemainingBullets.h"
#include "../GameProject/Game/EnemyKill.h"
using namespace std;

int Save::Reading()
{

	SaveData n;
	//�J��
	FILE* fp = fopen("SaveData.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	//�ǂݍ���
	fread(&n, sizeof(n), 1, fp);
	//�m�F�p
	//printf("HP = %d\nDansuu = %d\nRemaining = %d\nEnemyKill = %d\nKey1 = %d\nKey2 = %d\n", n.Hp, n.Dansuu, n.Remaining, n.EnemyKill, n.Key1, n.Key2);
	//����
	fclose(fp);

	//�v���C���[��T��
	Base* P = Base::FindObject(eId_Player);
	//�Z�[�u�f�[�^�̗̑͂��v���C���[�̗̑͂ɓǂݍ���
	P->m_Hp_Now = n.Hp;
	//�Z�[�u�f�[�^�̑��U�����v���C���[�̑��U���ɓǂݍ���
	BulletNumber::m_Dansuu = n.Dansuu;
	//�Z�[�u�f�[�^�̎c�e�����v���C���[�̎c�e���ɓǂݍ���
	RemainingBullets::m_Remaining = n.Remaining;
	//�Z�[�u�f�[�^�̓|�����G�̐������݂̓|�����G�̐��ɓǂݍ���
	EnemyKill::m_Score = n.EnemyKill;
	//�Z�[�u�f�[�^�ɏ������܂ꂽ�G���A1�̌��������Ă��邩�A�����Ă��Ȃ�����ǂݍ���
	P->Key1_Count = n.Key1;
	//�Z�[�u�f�[�^�ɏ������܂ꂽ�G���A2�̌��������Ă��邩�A�����Ă��Ȃ�����ǂݍ���
	P->Key2_Count = n.Key2;

	return 0;
}

int Save::Writing()
{
	//�v���C���[��T��
	Base* P = Base::FindObject(eId_Player);
	SaveData n;
	//�v���C���[�̗̑͂��Z�[�u�f�[�^�̗̑͂ɏ�������
	n.Hp = P->m_Hp_Now;
	//�v���C���[�̑��U�����Z�[�u�f�[�^�̑��U���ɏ�������
	n.Dansuu = BulletNumber::m_Dansuu;
	//�v���C���[�̎c�e�����Z�[�u�f�[�^�̎c�e���ɏ�������
	n.Remaining = RemainingBullets::m_Remaining;
	//���݂̓G��|���������Z�[�u�f�[�^�̓G��|�������ɏ�������
	n.EnemyKill = EnemyKill::m_Score;
	//�G���A1�̌��������Ă��邩�A�����Ă��Ȃ������Z�[�u�f�[�^�ɏ�������
	n.Key1 = P->Key1_Count;
	//�G���A2�̌��������Ă��邩�A�����Ă��Ȃ������Z�[�u�f�[�^�ɏ�������
	n.Key2 = P->Key2_Count;

	//�J��
	FILE* fp = fopen("SaveData.dat", "wb");
	//����"NULL"�Ȃ�
	if (fp == NULL)
	{
		return 0;
	}
	//��������
	fwrite(&n, sizeof(n), 1, fp);
	//�m�F�p
	//printf("HP = %d\nDansuu = %d\nRemaining = %d\nEnemyKill = %d\nKey1 = %d\nKey2 = %d\n", n.Hp, n.Dansuu, n.Remaining, n.EnemyKill, n.Key1, n.Key2);
	//����
	fclose(fp);
	return 0;
}