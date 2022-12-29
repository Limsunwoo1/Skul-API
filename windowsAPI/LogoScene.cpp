#include "LogoScene.h"
#include "PlayerBase.h"
#include "BackGround.h"
#include "Input.h"
#include "SceneManager.h"
#include "BackGround.h"
#include "EventManager.h"
#include "Camera.h"

namespace sw
{
	LogoScene::LogoScene()
	{

	}

	LogoScene::~LogoScene()
	{
		Scene::Release();
	}

	void LogoScene::Initialize()
	{
		BackGround* bg = new BackGround();
		bg->SetImage(L"LogoBack", L"Title_Art2.bmp");
		bg->Initialize();
		bg->SetPos(Vector2(800.f, 450.f));
		bg->SetScale(Vector2(1600.f, 900.f));
		bg->SetCamera(false);
		bg->SetAlpha(false);

		BackGround* Logo = new BackGround();
		Logo->SetImage(L"Logo", L"SkulLogo.bmp");
		Logo->Initialize();
		Logo->SetPos(Vector2(800.f, 470.f));
		Logo->SetScale(Vector2(600.f, 250));
		Logo->SetCamera(false);
		Logo->SetAlpha(false);

		BackGround* presseKey = new BackGround();
		presseKey->SetImage(L"presseKey", L"Inpress.bmp");
		presseKey->Initialize();
		presseKey->SetPos(Vector2(800.f, 650.f));
		presseKey->SetScale(Vector2(300, 50));
		presseKey->SetCamera(false);
		presseKey->SetAlpha(false);

		AddGameObject(bg, eColliderLayer::BackGround);
		AddGameObject(Logo, eColliderLayer::BackGround);
		AddGameObject(presseKey, eColliderLayer::BackGround);

	}

	void LogoScene::Tick()
	{
		// 오브젝트 tick 호출한다
		Scene::Tick();
		for (int c = 0; c < (int)eKeyCode::End; ++c)
		{
			if (KEY_DOWN((eKeyCode)c))
			{
				EventInfo info;
				info.Type = EventType::ChangeScene;
				info.Parameter1 = new eSceneType(eSceneType::Ch2Boss);

				EventManager::GetInstance()->EventPush(info);
			}
		}
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);

		wchar_t szFloat[50] = {};
		swprintf_s(szFloat, 50, L"Logo Scene");
		int strLen = wcsnlen_s(szFloat, 50);
		TextOut(hdc, 10, 30, szFloat, strLen);
	}
	void LogoScene::Enter()
	{
		Camera::GetInstance()->SetTarget(nullptr);
		Camera::GetInstance()->SetLookPosition(Vector2(1600.f, 900.f));
	}
}