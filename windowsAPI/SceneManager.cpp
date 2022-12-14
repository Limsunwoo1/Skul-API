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
		// �������� �ʱ�ȭ
		// �ٸ������� ������ ����Ϸ��� ������ 
		// ���� �켱������ �����Ǿ�� �Ѵ�.
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
		// �ڽ� > �θ� (��ĳ����)
		//mPlayScene = mScenes[(UINT)eSceneType::Tool];
		
		// �θ� > �ڽ� (�ٿ�ĳ����)
	}

	void SceneManager::Tick()
	{
		mPlayScene->Tick();
	}

	void SceneManager::Render(HDC hdc)
	{
		// ����� ������
		mPlayScene->Render(hdc);
	}

	void SceneManager::Release()
	{
		// ���α׷��� ����ɶ� �ѹ��� ȣ��
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