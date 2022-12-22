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
		bg1->SetImage(L"Back", L"BackGround.bmp");
		bg1->Initialize();
		bg1->SetPos(Vector2(100, 500.f));
		bg1->SetScale(Vector2(1600.f, 900.f));

		BackGround* bg2 = new BackGround();
		bg2->SetImage(L"Back", L"BackGround.bmp");
		bg2->Initialize();
		bg2->SetPos(Vector2(1700, 300.f));
		bg2->SetScale(Vector2(1600.f, 900.f));

		BackGround* bg3 = new BackGround();
		bg3->SetImage(L"Back", L"BackGround.bmp");
		bg3->Initialize();
		bg3->SetPos(Vector2(3300, 100.f));
		bg3->SetScale(Vector2(1600.f, 900.f));

		BackGround* bg4 = new BackGround();
		bg4->SetImage(L"Back", L"BackGround.bmp");
		bg4->Initialize();
		bg4->SetPos(Vector2(4900, 100.f));
		bg4->SetScale(Vector2(1600.f, 900.f));

		BackGround* bg5 = new BackGround();
		bg5->SetImage(L"Back", L"BackGround.bmp");
		bg5->Initialize();
		bg5->SetPos(Vector2(6500, 100.f));
		bg5->SetScale(Vector2(1600.f, 900.f));

		AddGameObject(bg1, eColliderLayer::BackGround);
		AddGameObject(bg2, eColliderLayer::BackGround);
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

		AddGameObject(monster4, eColliderLayer::Monster);
		AddGameObject(monster5, eColliderLayer::Monster);
		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);
		AddGameObject(monster6, eColliderLayer::Monster);
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
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Stage_1");

		/*CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster_ProjectTile);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster);*/
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Monster, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjectTile, eColliderLayer::Monster);

		ObjectManager::GetInstance()->AddObject(eSceneType::Play);
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
	}

	void PlayScene::Exit()
	{
		ObjectManager::GetInstance()->AddObject(eSceneType::Play);
		Camera::GetInstance()->SetTarget(nullptr);
	}
}