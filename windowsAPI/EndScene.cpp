#include "EndScene.h"
#include "PlayerBase.h"
#include "BackGround.h"
#include "Camera.h"

namespace sw
{
	EndScene::EndScene()
	{

	}

	EndScene::~EndScene()
	{
		Scene::Release();
	}

	void EndScene::Initialize()
	{
		BackGround* back1 = new BackGround();
		back1->SetImage(L"EndBack", L"FIi-mO5VUAAM1zL 복사.bmp");
		back1->SetPos(800.f, 450.f);
		back1->SetScale(1600.f, 900.f);
		back1->SetAlpha(true);
		back1->SetCamera(false);

		BackGround* back2 = new BackGround();
		back2->SetImage(L"EndBackLogo", L"EndLogo.bmp");
		back2->SetPos(750.f, 400.f);
		back2->SetScale(600.f, 400.f);
		back2->SetAlpha(false);
		back2->SetCamera(false);

		AddGameObject(back1, eColliderLayer::BackGround);
		AddGameObject(back2, eColliderLayer::BackGround);
	}

	void EndScene::Tick()
	{
		FadeInOut();
		// 오브젝트 tick 호출한다
		Scene::Tick();
	}

	void EndScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}

	void EndScene::Enter()
	{
		Camera::GetInstance()->SetTarget(nullptr);
		Camera::GetInstance()->SetLookPosition(Vector2(800.f, 450.f));
	}
	void EndScene::Exit()
	{
	}
}