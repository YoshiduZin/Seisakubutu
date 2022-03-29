#include "Base.h"

std::list<Base*> Base::m_List;

Base::Base(int Type_Id) : m_TypeId(Type_Id), m_Kill(false), m_Hit_Id(rand())
{
}

Base::~Base()
{

}

void Base::Update()
{
}

void Base::Render()
{
}

void Base::Draw()
{
}

void Base::Collision(Base* B)
{
}

void Base::CollisionCharctor(Base* B)
{
	V = B->m_Pos - m_Pos;
	L = V.LengthSq();
	if (L < pow(B->m_Rad + m_Rad, 2))
	{
		L = sqrt(L);
		S = (B->m_Rad + m_Rad) - L;
		Dir = V / L;
		B->m_Pos += Dir * S * 0.5f;
		m_Pos -= Dir * S * 0.5f;
	}
}

void Base::CollisionField(CModel* M)
{
	//モデルと球の衝突
	//衝突データ格納用
	CCollTriangle out[256];
	//押し戻し量
	CVector3D v(0, 0, 0);
	//球とモデルとの衝突
	int cnt = M->CollisionSphere(out, m_Pos + CVector3D(0, m_Rad, 0), m_Rad, 250);
	//接触した面の数繰り返す
	for (int i = 0; i < cnt; i++) {
		//接触した面が斜めより上を向いていたら地面
		if (out[i].m_normal.y > 0.5f) {
			//重力落下速度を0に戻す
			if (m_Vec.y < 0) {
				m_Vec.y = 0;
			}
		}
		float max_y = max(out[i].m_vertex[0].y, max(out[i].m_vertex[1].y, out[i].m_vertex[2].y));
		//接触した面の方向へ、めり込んだ分押し戻す
		CVector3D nv = out[i].m_normal * (m_Rad - out[i].m_dist);
		//最も大きな移動量を求める
		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
		//膝下までは乗り越える
		//膝上以上の壁のみ押し戻される
		if (max_y > m_Pos.y + 0.2f) {
			v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
			v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
		}
	}
	//押し戻す
	m_Pos += v;
}

bool Base::CollisionCapsule(Base* B1, Base* B2)
{
	return CCollision::CollisionCapsule(B1->LineS, B1->LineE, B1->m_Rad, B2->LineS, B2->LineE, B2->m_Rad);
}

bool Base::CollisionOBBShpere(Base* B1, Base* B2)
{
	return CCollision::CollisionOBBShpere(B1->A, B2->Center, B2->m_Rad, B2->Axis, B2->Length);
}

void Base::UpdateAll()
{
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		(*It)->Update();
	}
}

void Base::RenderAll()
{
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		(*It)->Render();
	}
}

void Base::DrawAll()
{
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		(*It)->Draw();
	}
}

void Base::KillALL()
{
	auto Itr = m_List.begin();
	//末尾まで繰り返す
	while (Itr != m_List.end()) {
		(*Itr)->m_Kill = true;
		Itr++;
	}
}

void Base::CollisionAll()
{
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		auto It2 = It;
		//次のオブジェクトへ
		It2++;
		for (; It2 != m_List.end(); It2++)
		{
			(*It)->Collision(*It2);
			(*It2)->Collision(*It);
		}
	}
}

void Base::KillCheck()
{
	for (auto It = m_List.begin(); It != m_List.end();) {
		//削除フラグがONなら
		if ((*It)->m_Kill) {
			//本体の削除
			delete (*It);
			//リストからの除外
			It = m_List.erase(It);
		}
		else {
			//次の要素へ
			It++;
		}
	}
}

void Base::Add(Base* B)
{
	m_List.push_back(B);
}

Base* Base::FindObject(int Type_Id)
{
	//m_Listの先頭から末尾までを繰り返す
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		//Type_Idと同じm_TypeIdを探してオブジェクトを返す
		if (Type_Id == (*It)->GetTypeId())
		{
			return (*It);
		}
	}
	//見つけれない場合
	return nullptr;
}

