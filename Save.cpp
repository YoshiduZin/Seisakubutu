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
	//開く
	FILE* fp = fopen("SaveData.dat", "rb");
	if (fp == NULL)
	{
		return 0;
	}
	//読み込み
	fread(&n, sizeof(n), 1, fp);
	//確認用
	//printf("HP = %d\nDansuu = %d\nRemaining = %d\nEnemyKill = %d\nKey1 = %d\nKey2 = %d\n", n.Hp, n.Dansuu, n.Remaining, n.EnemyKill, n.Key1, n.Key2);
	//閉じる
	fclose(fp);

	//プレイヤーを探す
	Base* P = Base::FindObject(eId_Player);
	//セーブデータの体力をプレイヤーの体力に読み込み
	P->m_Hp_Now = n.Hp;
	//セーブデータの装填数をプレイヤーの装填数に読み込み
	BulletNumber::m_Dansuu = n.Dansuu;
	//セーブデータの残弾数をプレイヤーの残弾数に読み込み
	RemainingBullets::m_Remaining = n.Remaining;
	//セーブデータの倒した敵の数を現在の倒した敵の数に読み込み
	EnemyKill::m_Score = n.EnemyKill;
	//セーブデータに書き込まれたエリア1の鍵を持っているか、持っていないかを読み込み
	P->Key1_Count = n.Key1;
	//セーブデータに書き込まれたエリア2の鍵を持っているか、持っていないかを読み込み
	P->Key2_Count = n.Key2;

	return 0;
}

int Save::Writing()
{
	//プレイヤーを探す
	Base* P = Base::FindObject(eId_Player);
	SaveData n;
	//プレイヤーの体力をセーブデータの体力に書き込み
	n.Hp = P->m_Hp_Now;
	//プレイヤーの装填数をセーブデータの装填数に書き込み
	n.Dansuu = BulletNumber::m_Dansuu;
	//プレイヤーの残弾数をセーブデータの残弾数に書き込み
	n.Remaining = RemainingBullets::m_Remaining;
	//現在の敵を倒した数をセーブデータの敵を倒した数に書き込み
	n.EnemyKill = EnemyKill::m_Score;
	//エリア1の鍵を持っているか、持っていないかをセーブデータに書き込み
	n.Key1 = P->Key1_Count;
	//エリア2の鍵を持っているか、持っていないかをセーブデータに書き込み
	n.Key2 = P->Key2_Count;

	//開く
	FILE* fp = fopen("SaveData.dat", "wb");
	//もし"NULL"なら
	if (fp == NULL)
	{
		return 0;
	}
	//書き込み
	fwrite(&n, sizeof(n), 1, fp);
	//確認用
	//printf("HP = %d\nDansuu = %d\nRemaining = %d\nEnemyKill = %d\nKey1 = %d\nKey2 = %d\n", n.Hp, n.Dansuu, n.Remaining, n.EnemyKill, n.Key1, n.Key2);
	//閉じる
	fclose(fp);
	return 0;
}