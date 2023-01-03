#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
namespace sw
{
	Scene::Scene()
		: mSceneChange(false)
	{
		mObjects.resize((UINT)eColliderLayer::END);
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		for (int y = 0; y < mObjects.size(); y++)
		{
			for (int x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;

				mObjects[y][x]->Initialize();
			}
		}
	}

	void Scene::Tick()
	{
		for (int y = 0; y < mObjects.size(); y++)
		{
			for (int x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;

				if (mObjects[y][x]->IsDeath())
					continue;

				mObjects[y][x]->Tick();
			}
		}
	}

	void Scene::Render(HDC hdc)
	{
		for (int y = 0; y < mObjects.size(); y++)
		{
			for (int x = 0; x < mObjects[y].size(); x++)
			{
				Vector2 pos = mObjects[y][x]->GetPos();
				pos = Camera::GetInstance()->CalculatePos(pos);
				if (mObjects[y][x] == nullptr)
					continue;

				if (mObjects[y][x]->IsDeath())
					continue;
				if (y != (int)eColliderLayer::BackGround
					&& y != (int)eColliderLayer::Player)
				{
					if (pos.x > 1600 + 100 || pos.x < 0 - 100)
						continue;
					if (pos.y > 900 + 100 || pos.y < 0 - 100)
						continue;
				}

				mObjects[y][x]->Render(hdc);
			}
		}
	}

	void Scene::AddGameObject(GameObject* object, eColliderLayer type)
	{
		if (object == nullptr)
			return;

		mObjects[(UINT)type].push_back(object);
	}

	void Scene::DeleteGameObject(GameObject* object, eColliderLayer type)
	{
		auto iter = mObjects[(UINT)type].begin();

		for (; iter != mObjects[(UINT)type].end(); ++iter)
		{
			if (*iter == object)
			{
				/*delete *iter;
				*iter = nullptr;*/

				mObjects[(UINT)type].erase(iter);
				return;
			}
		}
	}

	void Scene::Enter()
	{
	}

	void Scene::Exit()
	{
	}

	void Scene::Release()
	{
		for (int y = 0; y < mObjects.size(); y++)
		{
			for (int x = 0; x < mObjects[y].size(); x++)
			{
				if (mObjects[y][x] == nullptr)
					continue;

				delete mObjects[y][x];
				mObjects[y][x] = nullptr;
				
			}
		}
	}
}
