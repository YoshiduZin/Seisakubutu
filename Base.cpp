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
	//���f���Ƌ��̏Փ�
	//�Փ˃f�[�^�i�[�p
	CCollTriangle out[256];
	//�����߂���
	CVector3D v(0, 0, 0);
	//���ƃ��f���Ƃ̏Փ�
	int cnt = M->CollisionSphere(out, m_Pos + CVector3D(0, m_Rad, 0), m_Rad, 250);
	//�ڐG�����ʂ̐��J��Ԃ�
	for (int i = 0; i < cnt; i++) {
		//�ڐG�����ʂ��΂߂���������Ă�����n��
		if (out[i].m_normal.y > 0.5f) {
			//�d�͗������x��0�ɖ߂�
			if (m_Vec.y < 0) {
				m_Vec.y = 0;
			}
		}
		float max_y = max(out[i].m_vertex[0].y, max(out[i].m_vertex[1].y, out[i].m_vertex[2].y));
		//�ڐG�����ʂ̕����ցA�߂荞�񂾕������߂�
		CVector3D nv = out[i].m_normal * (m_Rad - out[i].m_dist);
		//�ł��傫�Ȉړ��ʂ����߂�
		v.y = fabs(v.y) > fabs(nv.y) ? v.y : nv.y;
		//�G���܂ł͏��z����
		//�G��ȏ�̕ǂ̂݉����߂����
		if (max_y > m_Pos.y + 0.2f) {
			v.x = fabs(v.x) > fabs(nv.x) ? v.x : nv.x;
			v.z = fabs(v.z) > fabs(nv.z) ? v.z : nv.z;
		}
	}
	//�����߂�
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
	//�����܂ŌJ��Ԃ�
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
		//���̃I�u�W�F�N�g��
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
		//�폜�t���O��ON�Ȃ�
		if ((*It)->m_Kill) {
			//�{�̂̍폜
			delete (*It);
			//���X�g����̏��O
			It = m_List.erase(It);
		}
		else {
			//���̗v�f��
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
	//m_List�̐擪���疖���܂ł��J��Ԃ�
	for (auto It = m_List.begin(); It != m_List.end(); It++)
	{
		//Type_Id�Ɠ���m_TypeId��T���ăI�u�W�F�N�g��Ԃ�
		if (Type_Id == (*It)->GetTypeId())
		{
			return (*It);
		}
	}
	//������Ȃ��ꍇ
	return nullptr;
}

