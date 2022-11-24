#include "PlayScene.h"
#include "Player.h"
#include "BackGround.h"
#include "Wood_Monster_1.h"
#include "Ground.h"

#include "MeteorControler.h"
#include "Input.h"
#include "SceneManager.h"
#include "CollisionManager.h"

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

		Ground* ground = new Ground();
		ground->SetPos(Vector2(100.f, 500.f));

		AddGameObject(bg,eColliderLayer::BackGround);
		AddGameObject(new Player(),eColliderLayer::Player);
		AddGameObject(ground, eColliderLayer::Ground);

		/*AddGameObject(ms1, eColliderLayer::Monster);
		AddGameObject(ms2, eColliderLayer::Monster);*/

	}

	void PlayScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();
		sw::MeteorControler::GetMeteorControler()->Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::GetInstance()->ChangeScene(eSceneType::End);
		}
	}

	void PlayScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
		//sw::MeteorControler::GetMeteorControler()->Render(hdc);


		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Paly Scene");
		int strLen = (int)wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void PlayScene::Enter()
	{
		/*CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster_ProjectTile);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Monster);*/
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
	}

	void PlayScene::Exit()
	{

	}
}