#include "Ch2BossScene.h"
#include "BackGround.h"
#include "LeianaBoss.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "LeianaControler.h"
#include "ObjectManager.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "Rigidbody.h"
#include "UIManager.h"
namespace sw
{
	Ch2BossScene::Ch2BossScene()
	{

	}
	Ch2BossScene::~Ch2BossScene()
	{
		delete mBoss;
		Scene::Release();
	}
	void Ch2BossScene::Initialize()
	{
		BackGround* bg = new BackGround();
		bg->SetImage(L"2CHBossBack", L"ch2_3 ����.bmp");
		bg->SetPos(Vector2(1200, 450.f));
		bg->SetScale(Vector2(2400.f, 900.f));

		AddGameObject(bg, eColliderLayer::BackGround);

		LeianaControler* Ch2Boss = new LeianaControler();
		Ch2Boss->SetPlayer(ObjectManager::GetInstance()->GetPlayer());
		mBoss = Ch2Boss;
		Ch2Boss->PushBoss(this);
	}
	void Ch2BossScene::Tick()
	{
		if (Camera::GetInstance()->GetCameraEffect() == eCameraEffect::FadeOut
			&& Camera::GetInstance()->GetCuttonAlpha() >= 1.0f)
		{
			Camera::GetInstance()->SetCameraEffect(eCameraEffect::FadeIn);
			Camera::GetInstance()->SetAlphaTime(0.0f);
		}

		if (Camera::GetInstance()->GetCameraEffect() == eCameraEffect::FadeIn
			&& Camera::GetInstance()->GetCuttonAlpha() <= 0.0f)
		{
			Camera::GetInstance()->SetCameraEffect(eCameraEffect::None);
			Camera::GetInstance()->SetAlphaTime(0.0f);
		}

		if(mBoss)
			mBoss->Tick();
		Scene::Tick();
	}
	void Ch2BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Ch2BossScene::Enter()
	{
		// �� ������ �ε�
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Ch2BossStage");
		// �ݸ��� ���̾�
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::BossMonster);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster_ProjecTile, eColliderLayer::Player);

		// �÷��̾�
		ObjectManager::GetInstance()->AddObject(eSceneType::Ch2Boss);
		ObjectManager::GetInstance()->GetPlayer()->SetPos(1200.f, 800.0f);
		if (ObjectManager::GetInstance()->GetPlayer()->GetPlayer())
			ObjectManager::GetInstance()->GetPlayer()->GetPlayer()->SetPos(1200.f, 800.0f);

		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(true);

		// ī�޶�
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
		Camera::GetInstance()->SetDistance(Vector2(1200.f, 0.0f));
		Camera::GetInstance()->SetCameraMaxPos(Vector2(2295.f, 950.f));
		Camera::GetInstance()->SetCameraLowPos(Vector2(126.f, 50));

		// ui
		UIManager::GetInstance()->Push(eUIType::HP_PANEL);
		UIManager::GetInstance()->Push(eUIType::HP);
		UIManager::GetInstance()->Push(eUIType::Character_Panel);
		UIManager::GetInstance()->Push(eUIType::Character_MainHead);
		UIManager::GetInstance()->Push(eUIType::Character);
		UIManager::GetInstance()->Push(eUIType::Skil_Panel);
	}
	void Ch2BossScene::Exit()
	{
		//�ݸ���
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground,false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::BossMonster, false);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster_ProjecTile, eColliderLayer::Player, false);
		// ������Ʈ
		ObjectManager::GetInstance()->DeleteObject(eSceneType::Ch2Boss);
		ObjectManager::GetInstance()->GetPlayer()->GetComponent<Rigidbody>()->SetGround(false);
		// ī�޶�
		Camera::GetInstance()->SetTarget(nullptr);

		// ui
		UIManager::GetInstance()->Pop(eUIType::HP_PANEL);
		UIManager::GetInstance()->Pop(eUIType::HP);
		UIManager::GetInstance()->Pop(eUIType::Character_Panel);
		UIManager::GetInstance()->Pop(eUIType::Character_MainHead);
		UIManager::GetInstance()->Pop(eUIType::Character);
		UIManager::GetInstance()->Pop(eUIType::Skil_Panel);
	}
}