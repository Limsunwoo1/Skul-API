#include "StartScene.h"
#include "ObjectManager.h"
#include "BackGround.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "MainPlayer.h"
#include "EventManager.h"
#include "Input.h"
#include "Rigidbody.h"
#include "PlayerBase.h"
#include "GateObject.h"
#include "Item.h"
#include "StaticObject.h"
#include "UIManager.h"

namespace sw
{
	StartScene::StartScene()
	{
	}
	StartScene::~StartScene()
	{
		Scene::Release();
	}

	void StartScene::Initialize()
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

		StaticObject* object = new StaticObject(L"StaticObject6");
		object->SetPos(750.f, 500.f);
		object->SetScale(3.f, 3.f);

		StaticObject* object1 = new StaticObject(L"StaticObject6");
		object1->SetPos(800.f, 500.f);
		object1->SetScale(3.f, 3.f);

		StaticObject* object2 = new StaticObject(L"StaticObject6");
		object2->SetPos(850.f, 500.f);
		object2->SetScale(3.f, 3.f);

		StaticObject* object3 = new StaticObject(L"StaticObject6");
		object3->SetPos(900.f, 500.f);
		object3->SetScale(3.f, 3.f);

		StaticObject* object4 = new StaticObject(L"StaticObject6");
		object4->SetPos(950.f, 500.f);
		object4->SetScale(3.f, 3.f);

		StaticObject* object5 = new StaticObject(L"StaticObject6");
		object5->SetPos(1000.f, 500.f);
		object5->SetScale(3.f, 3.f);

		StaticObject* object6 = new StaticObject(L"StaticObject6");
		object6->SetPos(1050.f, 500.f);
		object6->SetScale(3.f, 3.f);

		StaticObject* object7 = new StaticObject(L"StaticObject6");
		object7->SetPos(1050.f, 500.f);
		object7->SetScale(3.f, 3.f);

		StaticObject* object8 = new StaticObject(L"StaticObject6");
		object8->SetPos(1100.f, 500.f);
		object8->SetScale(3.f, 3.f);

		StaticObject* object9 = new StaticObject(L"StaticObject6");
		object9->SetPos(1150.f, 500.f);
		object9->SetScale(3.f, 3.f);

		StaticObject* object10 = new StaticObject(L"StaticObject6");
		object10->SetPos(1200.f, 500.f);
		object10->SetScale(3.f, 3.f);

		StaticObject* object11 = new StaticObject(L"StaticObject6");
		object11->SetPos(1250.f, 500.f);
		object11->SetScale(3.f, 3.f);

		StaticObject* object12 = new StaticObject(L"StaticObject6");
		object12->SetPos(1300.f, 500.f);
		object12->SetScale(3.f, 3.f);

		StaticObject* object13 = new StaticObject(L"StaticObject6");
		object13->SetPos(1350.f, 500.f);
		object13->SetScale(3.f, 3.f);

		AddGameObject(object, eColliderLayer::StaticObject);
		AddGameObject(object1, eColliderLayer::StaticObject);
		AddGameObject(object2, eColliderLayer::StaticObject);
		AddGameObject(object3, eColliderLayer::StaticObject);
		AddGameObject(object4, eColliderLayer::StaticObject);
		AddGameObject(object5, eColliderLayer::StaticObject);
		AddGameObject(object6, eColliderLayer::StaticObject);
		AddGameObject(object7, eColliderLayer::StaticObject);
		AddGameObject(object8, eColliderLayer::StaticObject);
		AddGameObject(object9, eColliderLayer::StaticObject);
		AddGameObject(object10, eColliderLayer::StaticObject);
		AddGameObject(object11, eColliderLayer::StaticObject);
		AddGameObject(object12, eColliderLayer::StaticObject);
		AddGameObject(object13, eColliderLayer::StaticObject);

		StaticObject* object14 = new StaticObject(L"StaticObject1");
		object14->SetPos(1500.f, 100.f);
		object14->SetScale(3.f, 4.f);

		StaticObject* object15 = new StaticObject(L"StaticObject1");
		object15->SetPos(1700.f, 100.f);
		object15->SetScale(3.f, 4.f);

		StaticObject* object16 = new StaticObject(L"StaticObject1");
		object16->SetPos(1900.f, 100.f);
		object16->SetScale(3.f, 4.f);

		AddGameObject(object14, eColliderLayer::StaticObject);
		AddGameObject(object15, eColliderLayer::StaticObject);
		AddGameObject(object16, eColliderLayer::StaticObject);

		GateObject* gate = new GateObject();
		gate->SetPos(2118.f, 470.f);
		gate->SetNextScene(eSceneType::Play2);
		AddGameObject(gate, eColliderLayer::Gate);

		Item* item = new Item();
		item->SetPos(1750.f, 540.f);
		item->SetHeadType(eSkulHead::Sword);
		AddGameObject(item, eColliderLayer::Gate);
	}
	void StartScene::Tick()
	{
		FadeInOut();

		Scene::Tick();
	}

	void StartScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void StartScene::Enter()
	{
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Starte");

		// 콜리젼 레이어
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Ground, eColliderLayer::Item);

		// 플레이어
		ObjectManager::GetInstance()->AddObject(eSceneType::Start);
		ObjectManager::GetInstance()->GetPlayer()->SetPos(640.f, 540.f);
		if (ObjectManager::GetInstance()->GetPlayer()->GetPlayer())
			ObjectManager::GetInstance()->GetPlayer()->GetPlayer()->SetPos(640.f, 540.f);

		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(true);

		// 카메라
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
		Camera::GetInstance()->SetCameraMaxPos(Vector2(2370.f, 900.f));
		Camera::GetInstance()->SetCameraLowPos(Vector2(542.f, 0.f));
		//ui
		UIManager::GetInstance()->Push(eUIType::HP_PANEL);
		UIManager::GetInstance()->Push(eUIType::HP);
		UIManager::GetInstance()->Push(eUIType::Character_Panel);
		UIManager::GetInstance()->Push(eUIType::Character_MainHead);
		UIManager::GetInstance()->Push(eUIType::Character);
		UIManager::GetInstance()->Push(eUIType::Skil_Panel);

		sw::Ch1Sound.Play(true);
	}

	void StartScene::Exit()
	{
		//콜리젼
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground,false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Ground, eColliderLayer::Item, false);
		// 오브젝트
		ObjectManager::GetInstance()->DeleteObject(eSceneType::Start);
		// 카메라
		Camera::GetInstance()->SetTarget(nullptr);
		// ui
		UIManager::GetInstance()->Pop(eUIType::HP_PANEL);
		UIManager::GetInstance()->Pop(eUIType::HP);
		UIManager::GetInstance()->Pop(eUIType::Character_Panel);
		UIManager::GetInstance()->Pop(eUIType::Character_MainHead);
		UIManager::GetInstance()->Pop(eUIType::Character);
		UIManager::GetInstance()->Pop(eUIType::Skil_Panel);
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