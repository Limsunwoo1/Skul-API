#include "SceneManager.h"
#include "LogoScene.h"
#include "PlayScene.h"
#include "PlayScene2.h"
#include "EndScene.h"
#include "ToolScene.h"
#include "Ch2BossScene.h"
#include "GameObject.h"
#include "EventManager.h"
#include "TilePalette.h"
#include "StartScene.h"
#include "MonsterBase.h"

namespace sw
{
	SceneManager::SceneManager()
		: mMonsterCount(0)
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

		mScenes[(UINT)eSceneType::Start] = new StartScene();
		mScenes[(UINT)eSceneType::Start]->Initialize();

		mScenes[(UINT)eSceneType::Play] = new PlayScene();
		mScenes[(UINT)eSceneType::Play]->Initialize();

		mScenes[(UINT)eSceneType::Play2] = new PlayScene2();
		mScenes[(UINT)eSceneType::Play2]->Initialize();

		mScenes[(UINT)eSceneType::Ch2Boss] = new Ch2BossScene();
		mScenes[(UINT)eSceneType::Ch2Boss]->Initialize();

		mScenes[(UINT)eSceneType::End] = new EndScene();
		mScenes[(UINT)eSceneType::End]->Initialize();


		ChangeScene(eSceneType::Logo);
		// �ڽ� > �θ� (��ĳ����)
		//mPlayScene = mScenes[(UINT)eSceneType::Tool];
		
		// �θ� > �ڽ� (�ٿ�ĳ����)
	}

	void SceneManager::Tick()
	{
		SetMonsterCount();
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

		if (mPlayScene)
		{
			mPlayScene->Exit();

			Scene* scene = SceneManager::GetInstance()->GetScene(eSceneType::Tool);
			ToolScene* tool = dynamic_cast<ToolScene*>(scene);
			if (tool != nullptr)
			{
				tool->GetTilePalete()->Reset();
			}
		}

		mPlayScene = mScenes[(UINT)type];
		mPlayScene->Enter();
	}
	eSceneType SceneManager::GetPlayeSceneType()
	{
		for (int i = (int)eSceneType::Logo; i < (int)eSceneType::End; ++i)
		{
			if (mPlayScene == mScenes[i])
				return (eSceneType)i;
		}
		return eSceneType::End;
	}
	void SceneManager::LoadTileMap(const std::wstring& path)
	{
		ToolScene* tool = dynamic_cast<ToolScene*>(mScenes[(UINT)eSceneType::Tool]);
		tool->LoadTilePalette(path);
	}
	void SceneManager::SetMonsterCount()
	{
		int count = GetPlayScene()->GetGameObject(eColliderLayer::Monster).size();
		mMonsterCount = count;
	}
	void SceneManager::ClearObject()
	{
		const std::vector<GameObject*>& Objects = GetPlayScene()->GetGameObject(eColliderLayer::Monster);

		for (GameObject* object : Objects)
		{
			if (object->GetPos().y > 20000.f)
				object->SetDeath(true);

			if (!object->IsDeath())
				continue;

			MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
			monster->ProejcTielDelte();

			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Monster);
			info.Parameter2 = object;

			EventManager::GetInstance()->EventPush(info);
		}
	}
}