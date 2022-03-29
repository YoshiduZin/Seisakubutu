#include "PlayerAttack.h"

PlayerAttack::PlayerAttack(const CVector3D& P, const CVector3D& D) : Base(eId_PlayerAttack)
{
	m_Bullet = COPY_RESOURCE("Bullet", CModelObj);
	m_Pos = P;
	m_Dir = D;
	Kill_Count = 0;
	m_Rad = 0.01;
}

void PlayerAttack::Update()
{
	Base* P = Base::FindObject(eId_Player);
	//m_Pos = P->m_Pos;
	m_Rot = P->m_Rot;
	LineS = m_Pos;
	m_Pos += m_Dir * 1;
	//カウントが100以上なら
	if (Kill_Count++ > 100)
	{
		//削除
		m_Kill = true;
	}
	LineE = m_Pos;
}

void PlayerAttack::Render()
{
	m_Bullet.SetPos(m_Pos);
	m_Bullet.SetRot(m_Rot);
	m_Bullet.SetScale(0.1, 0.1, 0.1);
	//銃弾の表示
	m_Bullet.Render();
	//Utility::DrawCapsule(LineS, LineE, m_Rad, CVector4D(0, 1, 0, 1));

}

void PlayerAttack::Collision(Base* B)
{
}
