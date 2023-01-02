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

namespace sw
{
	StartScene::StartScene()
	{
	}
	StartScene::~StartScene()
	{
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

		GateObject* gate = new GateObject();
		gate->SetPos(2118.f, 470.f);
		gate->SetNextScene(eSceneType::Play);
		AddGameObject(gate, eColliderLayer::Gate);
	}
	void StartScene::Tick()
	{
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			EventInfo info;
			info.Type = EventType::ChangeScene;
			info.Parameter1 = new eSceneType(eSceneType::Play);

			EventManager::GetInstance()->EventPush(info);
		}
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
	}

	void StartScene::Exit()
	{
		//콜리젼
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground,false);
		// 오브젝트
		ObjectManager::GetInstance()->DeleteObject(eSceneType::Start);
		// 카메라
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