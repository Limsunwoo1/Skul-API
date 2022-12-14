#include "PlayScene.h"
#include "PlayerBase.h"
#include "BackGround.h"
#include "Wood_Monster_1.h"
#include "Ground.h"
#include "BasicSkul.h"
#include "SwordSkul.h"
#include "EffectObject.h"
#include "MainPlayer.h"
#include "Input.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Sword_Monster.h"
#include "Collider.h"
#include <iostream>
namespace sw
{
	PlayScene::PlayScene()
	{

	}

	PlayScene::~PlayScene()
	{
		Scene::Release();
	}

	void PlayScene::Initialize()
	{
		BackGround* bg = new BackGround();
		bg->SetImage(L"Back", L"BackGround.bmp");
		bg->Initialize();
		bg->SetPos(Vector2(1600.f, 900.f));
		bg->SetScale(Vector2(3600.f, 1800.f));



		//SwordSkul* swordSkul = new SwordSkul();
		//BasicSkul* basicskul = new BasicSkul();
		MainPlayer* player = new MainPlayer();

		SwordMonster* monster1 = new SwordMonster();
		monster1->SetPos(Vector2(10.f, 300.f));
		monster1->SetScale(Vector2(4.f, 4.f));
		monster1->SetDirction(false);

		SwordMonster* monster2 = new SwordMonster();
		monster2->SetPos(Vector2(300.f, 300.f));
		monster2->SetScale(Vector2(4.f,4.f));

		SwordMonster* monster3 = new SwordMonster();
		monster3->SetPos(Vector2(500.f, 500.f));
		monster3->SetScale(Vector2(4.f, 4.f));

		AddGameObject(bg,eColliderLayer::BackGround);
		AddGameObject(player,eColliderLayer::Player);
		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);

		/*AttackCollider* R_attack1 = new AttackCollider(swordSkul);
		R_attack1->SetScale(Vector2(80.f, 80.f));
		R_attack1->SetOffset(Vector2(50.f, -25.f));
		R_attack1->SetName(L"R_Basic_AttackA");

		AttackCollider* R_attack2 = new AttackCollider(swordSkul);
		R_attack2->SetScale(Vector2(80.f, 80.f));
		R_attack2->SetOffset(Vector2(70.f, -25.f));
		R_attack2->SetName(L"R_Basic_AttackB");

		AttackCollider* L_attack1 = new AttackCollider(swordSkul);
		L_attack1->SetScale(Vector2(80.f, 80.f));
		L_attack1->SetOffset(Vector2(-50.f, -25.f));
		L_attack1->SetName(L"L_Basic_AttackA");

		AttackCollider* L_attack2 = new AttackCollider(swordSkul);
		L_attack2->SetScale(Vector2(80.f, 80.f));
		L_attack2->SetOffset(Vector2(-70.f, -25.f));
		L_attack2->SetName(L"L_Basic_AttackB");

		AddGameObject(R_attack1, eColliderLayer::Player_ProjectTile);
		AddGameObject(R_attack2, eColliderLayer::Player_ProjectTile);
		AddGameObject(L_attack1, eColliderLayer::Player_ProjectTile);
		AddGameObject(L_attack2, eColliderLayer::Player_ProjectTile);*/

		/*AddGameObject(ms1, eColliderLayer::Monster);
		AddGameObject(ms2, eColliderLayer::Monster);*/

	}

	void PlayScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::GetInstance()->ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Paly Scene");
		int strLen = (int)wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\TestTile");

		/*CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster_ProjectTile);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster);*/
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjectTile, eColliderLayer::Monster);
	}

	void PlayScene::Exit()
	{

	}
}