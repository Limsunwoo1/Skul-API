#include "SceneManager.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "PlayScene.h"
#include "EndScene.h"
#include "ToolScene.h"

namespace sw
{
	SceneManager::SceneManager()
	{

	}

	SceneManager::~SceneManager()
	{

	}

	void SceneManager::Initalize()
	{
		// 모든씬들을 초기화
		// 다른씬에서 툴씬을 사용하려면 툴씬이 
		// 제일 우선적으로 생성되어야 한다.
		mScenes[(UINT)eSceneType::Tool] = new ToolScene();
		mScenes[(UINT)eSceneType::Tool]->Initialize();

		mScenes[(UINT)eSceneType::Logo] = new LogoScene();
		mScenes[(UINT)eSceneType::Logo]->Initialize();

		mScenes[(UINT)eSceneType::Title] = new TitleScene();
		mScenes[(UINT)eSceneType::Title]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();


		ChangeScene(eSceneType::Logo);
		// 자식 > 부모 (업캐스팅)
		//mPlayScene = mScenes[(UINT)eSceneType::Tool];
		
		// 부모 > 자식 (다운캐스팅)
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		// 현재씬 렌더링
		mPlayScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		// 프로그램이 종료될때 한번만 호출
		for (Scene* scene : mScenes)
		{
			if (scene == nullptr)
				continue;

			delete scene;
			scene = nullptr;
		}
	}

	void SceneManager::ChangeScene(eSceneType type)
	{
		if (mScenes[(UINT)type] == nullptr)
			return;

		if(mPlayScene)
			mPlayScene->Exit();

		mPlayScene = mScenes[(UINT)type];
		mPlayScene->Enter();
	}
	void SceneManager::LoadTileMap(const std::wstring& path)
	{
		ToolScene* tool = dynamic_cast<ToolScene*>(mScenes[(UINT)eSceneType::Tool]);
		tool->LoadTilePalette(path);
	}
}