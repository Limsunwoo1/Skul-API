#include "LogoScene.h"
#include "PlayerBase.h"
#include "BackGround.h"
#include "Input.h"
#include "SceneManager.h"
#include "BackGround.h"
#include "EventManager.h"
#include "Camera.h"
#include "Sound.h"

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

		//Title.LoadWavFile(L"..\\Resource\\Sound\\MainTitle\\MainTitle.wav");
		//Title.SetVolume(20);
		//Title.SetKey(L"LogoSound");
		//Title.Play(true);
		sw::MainTitleSound.Play(true);
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
				info.Parameter1 = new eSceneType(eSceneType::Start);

				EventManager::GetInstance()->EventPush(info);

				Camera::GetInstance()->SetCameraEffect(eCameraEffect::FadeOut);
				Camera::GetInstance()->SetAlphaTime(2.0f);
			}
		}
	}

	void LogoScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void LogoScene::Enter()
	{
		Camera::GetInstance()->SetTarget(nullptr);
		Camera::GetInstance()->SetLookPosition(Vector2(1600.f, 900.f));
	}
	void LogoScene::Exit()
	{
		sw::MainTitleSound.Stop(true);
	}
}