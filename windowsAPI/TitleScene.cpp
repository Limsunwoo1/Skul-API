#include "TitleScene.h"
#include "Player.h"
#include "BackGround.h"
#include "MeteorControler.h"
#include "Input.h"
#include "SceneManager.h"

namespace sw
{
	TitleScene::TitleScene()
	{

	}

	TitleScene::~TitleScene()
	{
		Scene::Release();
	}

	void TitleScene::Initialize()
	{

	}

	void TitleScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();

		if (KEY_DOWN(eKeyCode::N))
		{
			SceneManager::GetInstance()->ChangeScene(eSceneType::Play);
		}
	}

	void TitleScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Title Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}

	void TitleScene::Enter()
	{
	}
	void TitleScene::Exit()
	{
	}
}