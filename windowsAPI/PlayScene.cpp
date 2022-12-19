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
		BackGround* bg = new BackGround();
		bg->SetImage(L"Back", L"BackGround.bmp");
		bg->Initialize();
		bg->SetPos(Vector2(4000, 100.f));
		bg->SetScale(Vector2(8000.f, 1800.f));



		//SwordSkul* swordSkul = new SwordSkul();
		//BasicSkul* basicskul = new BasicSkul();

		SwordMonster* monster1 = new SwordMonster();
		monster1->SetPos(Vector2(1665.f, 253.f));
		monster1->SetDirction(false);

		SwordMonster* monster2 = new SwordMonster();
		monster2->SetPos(Vector2(2300.f, 441.f));

		SwordMonster* monster3 = new SwordMonster();
		monster3->SetPos(Vector2(3600.f, 441.f));

		AxeMonster* monster4 = new AxeMonster();
		monster4->SetPos(Vector2(4000.f, 441.f));

		AxeMonster* monster5 = new AxeMonster();
		monster5->SetPos(Vector2(5200.f, 383.f));
		monster5->SetDirction(false);

		MaidMonster_1* monster6 = new MaidMonster_1();
		monster6->SetPos(Vector2(5400.f, 383));

		AddGameObject(bg,eColliderLayer::BackGround);
		AddGameObject(monster4, eColliderLayer::Monster);
		AddGameObject(monster5, eColliderLayer::Monster);
		AddGameObject(monster1, eColliderLayer::Monster);
		AddGameObject(monster2, eColliderLayer::Monster);
		AddGameObject(monster3, eColliderLayer::Monster);
		AddGameObject(monster6, eColliderLayer::Monster);

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