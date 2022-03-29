#include "Game.h"
#include "../Game/TutorialField.h"
#include "../Game/Camera.h"
#include "../Game/Player.h"
#include "../Game/PlayerWepon.h"
#include "../Game/Zombie.h"
#include "../Game/EnemyKill.h"
#include "../Game/BossEnemy.h"
#include "../Game/UI.h"
#include "../Game/Icon.h"
#include "../Game/Shikiri.h"
#include "../Game/BulletNumber.h"
#include "../Game/RemainingBullets.h"
#include "../Game/AmmoBox.h"
#include "../Game/Door.h"
#include "../Game/Key.h"
#include "../Game/HitCollision.h"
#include "../Screen/GameClear.h"
#include "../Screen/Title.h"
#include "../Game/Arrow.h"
#include "../Game/Sousa.h"
#include "../Game/SaveSpot.h"
#include "../Data/SaveData/Save.h"

Game::Game() : Base(eId_Game)
{
	Base::Add(new Title);
	//オブジェクトの追加
	Base::Add(new UI);
	Base::Add(new Player(CVector3D(45, 0, 48)));
	Base::Add(new Camera);
	Base::Add(new TitleField());
	Base::Add(new TutorialField());
	Base::Add(new Door1(CVector3D(-37.6, 4, 16), CVector3D(0, DtoR(-90), 0)));
	Base::Add(new Door2(CVector3D(-25.6, 0, -38.5), CVector3D(0, DtoR(180), 0)));
	Base::Add(new Arrow1(CVector3D(0, 10, 0)));
	Base::Add(new Arrow2(CVector3D(0, 0, 0)));
	Base::Add(new Sousa);
	Base::Add(new EnemyKill);
	Base::Add(new Icon);
	Base::Add(new Shikiri);
	Base::Add(new BulletNumber);
	Base::Add(new RemainingBullets);
	Base::Add(new EnemyCollision(CVector3D(40, 5, 34)));
	Base::Add(new BossCollision(CVector3D(-47.5, 5, 10)));
	Base::Add(new GameClear);
	Base::Add(new SaveSpot1(CVector3D(-49.5, 4, 15), CVector3D(0, 0, 0)));
}

Game::~Game()
{

}

void Game::Update()
{
	//保存テスト
	//if (PUSH(CInput::eMouseR))
	//{
	//	Save::Writing();
	//}
}

void Game::Render()
{

}

void Game::Draw()
{

}