#include "Ch2BossScene.h"
#include "BackGround.h"
#include "LeianaBoss.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Camera.h"
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
		bg->SetImage(L"2CHBossBack", L"ch2_3 บนป็.bmp");
		bg->Initialize();
		bg->SetPos(Vector2(1200, 450.f));
		bg->SetScale(Vector2(2400.f, 900.f));

		AddGameObject(bg, eColliderLayer::BackGround);

		LeianaBoss* ch2boss = new LeianaBoss();
		ch2boss->PushBoss(this);

		AddGameObject(ch2boss, eColliderLayer::EFFECT);
	}
	void Ch2BossScene::Tick()
	{
		Scene::Tick();
	}
	void Ch2BossScene::Render(HDC hdc)
	{
		Scene::Render(hdc);
	}
	void Ch2BossScene::Enter()
	{
		SceneManager::GetInstance()->LoadTileMap(L"..\\Resource\\TileData\\Ch2BossStage");
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster, eColliderLayer::Ground);
		Camera::GetInstance()->SetToolMode(true);
	}
	void Ch2BossScene::Exit()
	{

	}
	void Ch2BossScene::Release()
	{

	}
}