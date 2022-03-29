#include "PlayerWepon.h"

PlayerWepon::PlayerWepon() : Base(eId_Wepon)
{
	m_PlayerWepon = COPY_RESOURCE("Wepon", CModelObj);
}

void PlayerWepon::Update()
{
}

void PlayerWepon::Render()
{
	//•Ší‚Ì•\¦(s—ñw’è)
	m_PlayerWepon.Render(Player_Wepon_Matrix);
}