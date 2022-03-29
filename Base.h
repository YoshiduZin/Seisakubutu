#pragma once
#include "../stdafx.h"
#include "../GID.h"
#define GRVITY (0.1f/20);

class Base
{
private:
	//タイプID
	int m_TypeId;
	//
	static std::list<Base*> m_List;

public:
	//3D座標
	CVector3D m_Pos;
	//過去の座標
	CVector3D m_Pos_Old;
	//回転値
	CVector3D m_Rot;
	//移動量
	CVector3D m_Vec;
	CVector3D V;
	CVector3D Dir;
	CVector3D LineS;
	CVector3D LineE;
	CVector3D Center;
	CVector3D* Axis;
	COBB A;
	//半径
	float m_Rad;
	float L;
	float S;
	float* Length;
	int Count;
	int m_Hit_Id;
	int m_Hp_Now;
	/* キーを持っているか */
	int Key1_Count;
	int Key2_Count;
	//削除フラグ
	bool m_Kill;
	bool m_Death = false;
	/* ボス用の関数 */
	//攻撃フラグ
	bool m_Attack1 = false;
	bool m_Attack2 = false;
	bool m_Syutugen = false;

public:
	Base(int Type_Id);
	virtual ~Base();
	//タイプ種別の所得
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
	//キャラクターの衝突検証
	void CollisionCharctor(Base* B);
	//フィールドの衝突検証
	void CollisionField(CModel* M);
	//カプセルの衝突検証
	static bool CollisionCapsule(Base* B1, Base* B2);
	//四角の衝突検証
	static bool CollisionOBBShpere(Base* B1, Base* B2);
	//全てのオブジェクトの削除
	static void KillALL();
	//全てのオブジェクトの更新
	static void UpdateAll();
	//全てのオブジェクトの描画(3Dモデル)
	static void RenderAll();
	//全てのオブジェクトの描画(UI)
	static void DrawAll();
	//全てのオブジェクト同士の衝突検証
	static void CollisionAll();
	//全てのオブジェクトの削除チェック
	static void KillCheck();
	//オブジェクトを追加
	static void Add(Base* B);
	//オブジェクトの検索
	static Base* FindObject(int Type_Id);
};