#pragma once
#include "../GameProject/Base/Base.h"

class Save
{
private:
	struct SaveData
	{
		int Hp;				//�v���C���[�̗̑�
		int Dansuu;			//���U��
		int Remaining;		//�c�e��
		int EnemyKill;		//�|�����G�̐�
		int Key1;			//�G���A1�̌��������Ă��邩
		int Key2;			//�G���A2�̌��������Ă��邩
	};

public:
	//�ǂݍ���
	static int Reading();
	//��������
	static int Writing();
};