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
#include "StaticObject.h"
#include "UIManager.h"

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
		/*SwordMonster* monster1 = new SwordMonster();
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
		monster6->SetPos(Vector2(5400.f, 350.f));*/

		/*AddGameObject(monster4, eColliderLayer::Monster);
		AddGameObject(monster5, eColliderLayer::Monster);
		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);
		AddGameObject(monster6, eColliderLayer::Monster);*/

		StaticObject* object = new StaticObject(L"StaticObject5");
		object->SetPos(300.f,790);
		object->SetScale(4.f, 4.f);

		StaticObject* object1 = new StaticObject(L"StaticObject5");
		object1->SetPos(370.f, 790);
		object1->SetScale(4.f, 4.f);

		StaticObject* object2 = new StaticObject(L"StaticObject5");
		object2->SetPos(440.f, 790);
		object2->SetScale(4.f, 4.f);

		StaticObject* object3 = new StaticObject(L"StaticObject5");
		object3->SetPos(510.f, 790);
		object3->SetScale(4.f, 4.f);

		StaticObject* object4 = new StaticObject(L"StaticObject5");
		object4->SetPos(580.f, 790);
		object4->SetScale(4.f, 4.f);

		StaticObject* object5 = new StaticObject(L"StaticObject5");
		object5->SetPos(650.f, 790);
		object5->SetScale(4.f, 4.f);

		StaticObject* object6 = new StaticObject(L"StaticObject5");
		object6->SetPos(730.f, 790);
		object6->SetScale(4.f, 4.f);

		AddGameObject(object, eColliderLayer::StaticObject);
		AddGameObject(object1, eColliderLayer::StaticObject);
		AddGameObject(object2, eColliderLayer::StaticObject);
		AddGameObject(object3, eColliderLayer::StaticObject);
		AddGameObject(object4, eColliderLayer::StaticObject);
		AddGameObject(object5, eColliderLayer::StaticObject);
		AddGameObject(object6, eColliderLayer::StaticObject);

		StaticObject* object7_1 = new StaticObject(L"StaticObject2");
		object7_1->SetPos(1770.f, 640.f);
		object7_1->SetScale(2.f, 2.f);

		StaticObject* object8_1 = new StaticObject(L"StaticObject2");
		object8_1->SetPos(1840.f, 600.f);
		object8_1->SetScale(2.f, 3.f);

		StaticObject* object9_1 = new StaticObject(L"StaticObject2");
		object9_1->SetPos(1910.f, 640.f);
		object9_1->SetScale(2.f, 2.f);

		AddGameObject(object7_1, eColliderLayer::StaticObject);
		AddGameObject(object8_1, eColliderLayer::StaticObject);
		AddGameObject(object9_1, eColliderLayer::StaticObject);

		StaticObject* object7 = new StaticObject(L"StaticObject1");
		object7->SetPos(800.f, 200.f);
		object7->SetScale(4.f, 3.f);

		StaticObject* object8 = new StaticObject(L"StaticObject1");
		object8->SetPos(1500.f, 200.f);
		object8->SetScale(4.f, 3.f);

		StaticObject* object9 = new StaticObject(L"StaticObject1");
		object9->SetPos(2200.f, 200.f);
		object9->SetScale(4.f, 3.f);

		StaticObject* object10 = new StaticObject(L"StaticObject1");
		object10->SetPos(2900.f, 200.f);
		object10->SetScale(4.f, 3.f);

		StaticObject* object11 = new StaticObject(L"StaticObject1");
		object11->SetPos(3600.f, 200.f);
		object11->SetScale(4.f, 3.f);

		StaticObject* object12 = new StaticObject(L"StaticObject1");
		object12->SetPos(4300.f, 200.f);
		object12->SetScale(4.f, 3.f);


		AddGameObject(object7, eColliderLayer::StaticObject);
		AddGameObject(object8, eColliderLayer::StaticObject);
		AddGameObject(object9, eColliderLayer::StaticObject);
		AddGameObject(object10, eColliderLayer::StaticObject);
		AddGameObject(object11, eColliderLayer::StaticObject);
		AddGameObject(object12, eColliderLayer::StaticObject);

		StaticObject* object14 = new StaticObject(L"StaticObject14");
		object14->SetPos(2200.f, 660.f);
		object14->SetScale(4.f, 4.f);

		StaticObject* object15 = new StaticObject(L"StaticObject12");
		object15->SetPos(2100.f, 660.f);
		object15->SetScale(4.f, 4.f);

		AddGameObject(object14, eColliderLayer::StaticObject);
		AddGameObject(object15, eColliderLayer::StaticObject);

		StaticObject* object16 = new StaticObject(L"StaticObject13");
		object16->SetPos(2540.f, 1300.f);
		object16->SetScale(4.f, 4.f);

		StaticObject* object17 = new StaticObject(L"StaticObject15");
		object17->SetPos(3350.f, 1300.f);
		object17->SetScale(4.f, 4.f);

		AddGameObject(object16, eColliderLayer::StaticObject);
		AddGameObject(object17, eColliderLayer::StaticObject);

		StaticObject* object18 = new StaticObject(L"StaticObject2");
		object18->SetPos(3800.f, 640.f);
		object18->SetScale(2.f, 2.f);

		StaticObject* object19 = new StaticObject(L"StaticObject2");
		object19->SetPos(3870.f, 600.f);
		object19->SetScale(2.f, 3.f);

		StaticObject* object20 = new StaticObject(L"StaticObject2");
		object20->SetPos(3940.f, 640.f);
		object20->SetScale(2.f, 2.f);

		AddGameObject(object18, eColliderLayer::StaticObject);
		AddGameObject(object19, eColliderLayer::StaticObject);
		AddGameObject(object20, eColliderLayer::StaticObject);

		GateObject* gate = new GateObject();
		gate->SetPos(4750.f, 600.f);
		gate->SetNextScene(eSceneType::Play);
		AddGameObject(gate, eColliderLayer::Gate);

		Item* item = new Item();
		item->SetPos(4350.f, 670.f);
		item->SetHeadType(eSkulHead::Samurai);
		AddGameObject(item, eColliderLayer::Gate);
	}

	void PlayScene2::Tick()
	{
		FadeInOut();

		// 오브젝트 tick 호출한다
		Scene::Tick();
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
		Camera::GetInstance()->SetCameraLowPos(Vector2(20.f, 50.f));
		//ui
		vector<GameObject*>& objects = this->GetGameObject(eColliderLayer::Monster);
		for (GameObject* object : objects)
		{
			MonsterBase* monster = dynamic_cast<MonsterBase*>(object);

			if (monster == nullptr)
				continue;

			monster->PushUi();
		}

		UIManager::GetInstance()->Push(eUIType::HP_PANEL);
		UIManager::GetInstance()->Push(eUIType::HP);
		UIManager::GetInstance()->Push(eUIType::Character_Panel);
		UIManager::GetInstance()->Push(eUIType::Character_MainHead);
		UIManager::GetInstance()->Push(eUIType::Character);
		UIManager::GetInstance()->Push(eUIType::Skil_Panel);
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
		// ui
		UIManager::GetInstance()->Pop(eUIType::HP_PANEL);
		UIManager::GetInstance()->Pop(eUIType::HP);
		UIManager::GetInstance()->Pop(eUIType::Character_Panel);
		UIManager::GetInstance()->Pop(eUIType::Character_MainHead);
		UIManager::GetInstance()->Pop(eUIType::Character);
		UIManager::GetInstance()->Pop(eUIType::Skil_Panel);
		UIManager::GetInstance()->MonsterHpClear();
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