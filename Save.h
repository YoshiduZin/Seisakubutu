#pragma once
#include "../GameProject/Base/Base.h"

class Save
{
private:
	struct SaveData
	{
		int Hp;				//プレイヤーの体力
		int Dansuu;			//装填数
		int Remaining;		//残弾数
		int EnemyKill;		//倒した敵の数
		int Key1;			//エリア1の鍵をもっているか
		int Key2;			//エリア2の鍵を持っているか
	};

public:
	//読み込み
	static int Reading();
	//書き込み
	static int Writing();
};