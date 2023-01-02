#include "PlayScene2.h"
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
#include "AxeMonster.h"
#include "Collider.h"
#include "Camera.h"
#include <iostream>
#include "UtilLog.h"
#include "MaidMonster_1.h"
#include "ObjectManager.h"
#include "EventManager.h"
#include "Rigidbody.h"
#include "GateObject.h"
#include "Item.h"

namespace sw
{
	PlayScene2::PlayScene2()
	{

	}

	PlayScene2::~PlayScene2()
	{
		Scene::Release();
	}

	void PlayScene2::Initialize()
	{
		// 배경
		BackGround* bg1 = new BackGround();
		bg1->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg1->Initialize();
		bg1->SetPos(Vector2(100, 500.f));
		bg1->SetScale(Vector2(1600.f, 1100.f));

		BackGround* bg2 = new BackGround();
		bg2->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg2->Initialize();
		bg2->SetPos(Vector2(1700, 500));
		bg2->SetScale(Vector2(1600.f, 1100.f));

		BackGround* bg3 = new BackGround();
		bg3->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg3->Initialize();
		bg3->SetPos(Vector2(3300, 500));
		bg3->SetScale(Vector2(1600.f, 1100.f));

		BackGround* bg3_1 = new BackGround();
		bg3_1->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg3_1->Initialize();
		bg3_1->SetPos(Vector2(3300, 800));
		bg3_1->SetScale(Vector2(1600.f, 1100.f));

		BackGround* bg4 = new BackGround();
		bg4->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg4->Initialize();
		bg4->SetPos(Vector2(4900, 500));
		bg4->SetScale(Vector2(1600.f, 1100.f));

		BackGround* bg5 = new BackGround();
		bg5->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg5->Initialize();
		bg5->SetPos(Vector2(6500, 500));
		bg5->SetScale(Vector2(1600.f, 1100.f));

		AddGameObject(bg1, eColliderLayer::BackGround);
		AddGameObject(bg2, eColliderLayer::BackGround);
		AddGameObject(bg3_1, eColliderLayer::BackGround);
		AddGameObject(bg3, eColliderLayer::BackGround);
		AddGameObject(bg4, eColliderLayer::BackGround);
		AddGameObject(bg5, eColliderLayer::BackGround);

		// 몬스터
		SwordMonster* monster1 = new SwordMonster();
		monster1->SetPos(Vector2(1665.f, 200.f));
		monster1->SetDirction(false);

		SwordMonster* monster2 = new SwordMonster();
		monster2->SetPos(Vector2(2300.f, 400.f));

		SwordMonster* monster3 = new SwordMonster();
		monster3->SetPos(Vector2(3600.f, 400.f));

		AxeMonster* monster4 = new AxeMonster();
		monster4->SetPos(Vector2(4000.f, 400.f));

		AxeMonster* monster5 = new AxeMonster();
		monster5->SetPos(Vector2(5600.f, 350.f));
		monster5->SetDirction(false);

		MaidMonster_1* monster6 = new MaidMonster_1();
		monster6->SetPos(Vector2(5400.f, 350.f));

		/*AddGameObject(monster4, eColliderLayer::Monster);
		AddGameObject(monster5, eColliderLayer::Monster);
		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);
		AddGameObject(monster6, eColliderLayer::Monster);*/

		GateObject* gate = new GateObject();
		gate->SetPos(4750.f, 600.f);
		gate->SetNextScene(eSceneType::Ch2Boss);
		gate->SetBossGate(true);
		AddGameObject(gate, eColliderLayer::Gate);

		Item* item = new Item();
		item->SetPos(4350.f, 670.f);
		AddGameObject(item, eColliderLayer::Gate);
	}

	void PlayScene2::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			EventInfo info;
			info.Type = EventType::ChangeScene;
			info.Parameter1 = new eSceneType(eSceneType::Ch2Boss);

			EventManager::GetInstance()->EventPush(info);
		}
	}

	void PlayScene2::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void PlayScene2::Enter()
	{
		// 맵데이터 로드
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Stage_2");

		// 콜리젼 레이어
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Item, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::Monster);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster_ProjecTile, eColliderLayer::Player);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate);

		// 플레이어
		ObjectManager::GetInstance()->AddObject(eSceneType::Play2);
		ObjectManager::GetInstance()->GetPlayer()->SetPos(114.f, 860.f);
		if (ObjectManager::GetInstance()->GetPlayer()->GetPlayer())
			ObjectManager::GetInstance()->GetPlayer()->GetPlayer()->SetPos(114.f, 860.f);
		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(true);
		// 카메라
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
		Camera::GetInstance()->SetCameraMaxPos(Vector2(5138.f, 1400.f));
		Camera::GetInstance()->SetCameraLowPos(Vector2(20.f, 0.f));
	}
	void PlayScene2::Exit()
	{
		// 콜리젼
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Item, eColliderLayer::Ground, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::Monster, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster_ProjecTile, eColliderLayer::Player, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate,false);
		// 오브젝트
		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(false);
		ObjectManager::GetInstance()->DeleteObject(eSceneType::Play2);
		//카메라
		Camera::GetInstance()->SetTarget(nullptr);
		// 타일데이터
		vector<GameObject*>& objects = this->GetGameObject(eColliderLayer::Tile);
		for (GameObject* object : objects)
		{
			object->SetDeath(true);
			delete object;
		}
		objects.clear();
	}
}