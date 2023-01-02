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
	PlayScene::PlayScene()
	{
		LOG_TODO("로그 예시 코드 확인했으면 지워도 무방");
		LOG("일반 로그 테스트");
		WARN_LOG("경고 로그 테스트");
		ERROR_LOG("에러 로그 테스트");
		ETC1_LOG("커스텀 로그 테스트");
		LOG(STRING("문자열 포매팅 테스트 : %d !!!", 30));
	}

	PlayScene::~PlayScene()
	{
		Scene::Release();
	}

	void PlayScene::Initialize()
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

		BackGround* bg6 = new BackGround();
		bg6->SetImage(L"Back", L"01 #57758 복사.bmp");
		bg6->Initialize();
		bg6->SetPos(Vector2(8100, 500));
		bg6->SetScale(Vector2(1600.f, 1100.f));

		AddGameObject(bg1, eColliderLayer::BackGround);
		AddGameObject(bg2, eColliderLayer::BackGround);
		AddGameObject(bg3_1, eColliderLayer::BackGround);
		AddGameObject(bg3, eColliderLayer::BackGround);
		AddGameObject(bg4, eColliderLayer::BackGround);
		AddGameObject(bg5, eColliderLayer::BackGround);
		AddGameObject(bg6, eColliderLayer::BackGround);

		AxeMonster* monster1 = new AxeMonster();
		monster1->SetPos(Vector2(2800, 350.f));

		AxeMonster* monster2 = new AxeMonster();
		monster2->SetPos(Vector2(3900.f, 350.f));
		monster2->SetDirction(false);

		AxeMonster* monster3 = new AxeMonster();
		monster3->SetPos(Vector2(5950.f, 270.f));
		monster3->SetDirction(false);

		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);
		// 몬스터
		SwordMonster* monster4 = new SwordMonster();
		monster4->SetPos(Vector2(1561.f, 160.f));
		monster4->SetDirction(false);

		SwordMonster* monster5 = new SwordMonster();
		monster5->SetPos(Vector2(1808.f, 160.f));

		SwordMonster* monster6 = new SwordMonster();
		monster6->SetPos(Vector2(2023.f, 345.f));

		SwordMonster* monster7 = new SwordMonster();
		monster7->SetPos(Vector2(2256.f, 345.f));

		SwordMonster* monster8 = new SwordMonster();
		monster8->SetPos(Vector2(2300.f, 345.f));
		monster8->SetDirction(false);

		SwordMonster* monster9 = new SwordMonster();
		monster9->SetPos(Vector2(2800.f, 345.f));
		monster9->SetDirction(false);

		SwordMonster* monster10 = new SwordMonster();
		monster10->SetPos(Vector2(2900.f, 345.f));
		monster10->SetDirction(false);

		SwordMonster* monster11 = new SwordMonster();
		monster11->SetPos(Vector2(3300.f, 345.f));
		monster11->SetDirction(false);

		SwordMonster* monster12 = new SwordMonster();
		monster12->SetPos(Vector2(3400.f, 345.f));
		monster12->SetDirction(false);

		SwordMonster* monster13 = new SwordMonster();
		monster13->SetPos(Vector2(3800.f, 345.f));
		monster13->SetDirction(false);

		SwordMonster* monster14 = new SwordMonster();
		monster14->SetPos(Vector2(3900.f, 345.f));

		SwordMonster* monster15 = new SwordMonster();
		monster15->SetPos(Vector2(3980.f, 345.f));
		monster15->SetDirction(false);

		SwordMonster* monster16 = new SwordMonster();
		monster16->SetPos(Vector2(4200.f, 345.f));

		SwordMonster* monster17 = new SwordMonster();
		monster17->SetPos(Vector2(4300.f, 345.f));
		monster17->SetDirction(false);

		SwordMonster* monster18 = new SwordMonster();
		monster18->SetPos(Vector2(4370.f, 345.f));
		monster18->SetDirction(false);

		SwordMonster* monster19 = new SwordMonster();
		monster19->SetPos(Vector2(4600.f, 345.f));

		SwordMonster* monster20 = new SwordMonster();
		monster20->SetPos(Vector2(4680.f, 345.f));
		monster20->SetDirction(false);

		SwordMonster* monster21 = new SwordMonster();
		monster21->SetPos(Vector2(4700.f, 345.f));

		SwordMonster* monster22 = new SwordMonster();
		monster22->SetPos(Vector2(4900.f, 270.f));
		monster22->SetDirction(false);

		SwordMonster* monster23 = new SwordMonster();
		monster23->SetPos(Vector2(5000.f, 270.f));
		monster23->SetDirction(false);

		/*AddGameObject(monster4, eColliderLayer::Monster);
		AddGameObject(monster5, eColliderLayer::Monster);
		AddGameObject(monster6, eColliderLayer::Monster);
		AddGameObject(monster7, eColliderLayer::Monster);
		AddGameObject(monster8, eColliderLayer::Monster);
		AddGameObject(monster9, eColliderLayer::Monster);
		AddGameObject(monster10, eColliderLayer::Monster);
		AddGameObject(monster11, eColliderLayer::Monster);
		AddGameObject(monster12, eColliderLayer::Monster);
		AddGameObject(monster13, eColliderLayer::Monster);
		AddGameObject(monster14, eColliderLayer::Monster);
		AddGameObject(monster15, eColliderLayer::Monster);
		AddGameObject(monster16, eColliderLayer::Monster);
		AddGameObject(monster17, eColliderLayer::Monster);
		AddGameObject(monster18, eColliderLayer::Monster);
		AddGameObject(monster19, eColliderLayer::Monster);
		AddGameObject(monster20, eColliderLayer::Monster);
		AddGameObject(monster21, eColliderLayer::Monster);
		AddGameObject(monster22, eColliderLayer::Monster);
		AddGameObject(monster23, eColliderLayer::Monster);*/

		MaidMonster_1* monster24 = new MaidMonster_1();
		monster24->SetPos(Vector2(5800.f, 270.f));

		MaidMonster_1* monster25 = new MaidMonster_1();
		monster25->SetPos(Vector2(5900.f, 270.f));

		MaidMonster_1* monster26 = new MaidMonster_1();
		monster26->SetPos(Vector2(6000.f, 270.f));

		AddGameObject(monster24, eColliderLayer::Monster);
		AddGameObject(monster25, eColliderLayer::Monster);
		AddGameObject(monster26, eColliderLayer::Monster);

		GateObject* gate = new GateObject();
		gate->SetPos(8200.f, 280.f);
		gate->SetNextScene(eSceneType::Play2);
		AddGameObject(gate, eColliderLayer::Gate);

		Item* item = new Item();
		item->SetPos(7800.f, 350.f);
		AddGameObject(item, eColliderLayer::Gate);
	}

	void PlayScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			EventInfo info;
			info.Type = EventType::ChangeScene;
			info.Parameter1 = new eSceneType(eSceneType::Play2);

			EventManager::GetInstance()->EventPush(info);
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
		// 맵데이터 로드
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Stage_1");

		// 콜리젼 레이어
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Item, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::Monster);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster_ProjecTile, eColliderLayer::Player);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate);

		// 플레이어
		ObjectManager::GetInstance()->AddObject(eSceneType::Play);
		ObjectManager::GetInstance()->GetPlayer()->SetPos(165.f, 800.f);
		if (ObjectManager::GetInstance()->GetPlayer()->GetPlayer())
			ObjectManager::GetInstance()->GetPlayer()->GetPlayer()->SetPos(165.f, 800.f);
		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(true);
		// 카메라
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
		Camera::GetInstance()->SetCameraMaxPos(Vector2(8550.f, 4666.f));
		Camera::GetInstance()->SetCameraLowPos(Vector2(64.f, 0.f));
	}

	void PlayScene::Exit()
	{
		// 콜리젼
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground,false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Item, eColliderLayer::Ground, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::Monster, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster_ProjecTile, eColliderLayer::Player, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Item, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Gate, false);
		//오브젝트
		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(false);
		ObjectManager::GetInstance()->DeleteObject(eSceneType::Play);
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