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
namespace sw
{
	Ch2BossScene::Ch2BossScene()
	{

	}
	Ch2BossScene::~Ch2BossScene()
	{
	}
	void Ch2BossScene::Initialize()
	{
		BackGround* bg = new BackGround();
		bg->SetImage(L"2CHBossBack", L"ch2_3 복사.bmp");
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
		// 맵 데이터 로드
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Ch2BossStage");
		// 콜리젼 레이어
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::Ground);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player_ProjecTile, eColliderLayer::BossMonster);
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster_ProjecTile, eColliderLayer::Player);

		// 플레이어
		ObjectManager::GetInstance()->AddObject(eSceneType::Ch2Boss);
		ObjectManager::GetInstance()->GetPlayer()->SetPos(1200.f, 0.0f);
		ObjectManager::GetInstance()->GetPlayer()->GetPlayer()->SetPos(1200.f, 0.0f);
		ObjectManager::GetInstance()->GetPlayer()->GetNextPlayer()->SetPos(1200.f, 0.0f);

		// 카메라
		Camera::GetInstance()->SetTarget(ObjectManager::GetInstance()->GetPlayer());
		Camera::GetInstance()->SetDistance(Vector2(1200.f, 0.0f));
		Camera::GetInstance()->SetCameraMaxPos(Vector2(2295.f, 950.f));
		Camera::GetInstance()->SetCameraLowPos(Vector2(126.f, 50));
	}
	void Ch2BossScene::Exit()
	{
	}
	void Ch2BossScene::Release()
	{

	}
}