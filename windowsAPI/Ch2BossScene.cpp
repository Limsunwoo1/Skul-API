#include "Ch2BossScene.h"
#include "BackGround.h"
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

	}
	void Ch2BossScene::Exit()
	{

	}
	void Ch2BossScene::Release()
	{

	}
}