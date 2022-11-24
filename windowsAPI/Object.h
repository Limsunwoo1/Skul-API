#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "SceneManager.h"

namespace sw
{
	namespace object
	{
		template <typename T>
		static __forceinline T* Instantiate(eColliderLayer type)
		{
			T* gameObject = new T();
			Scene* scene = SceneManager::GetInstance()->GetPlayScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		template <typename T>
		static __forceinline T* Instantiate(Vector2 position, eColliderLayer type)
		{
			T* gameObject = new T(position);
			Scene* scene = SceneManager::GetInstance()->GetPlayScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		template <typename T>
		static __forceinline void Destroy(GameObject* gameobj)
		{
			gameobj->Deth();
		}

		template <typename T>
		static __forceinline void Release()
		{
			Scene* scene = SceneManager::GetInstance()->GetPlayScene();
			std::vector<std::vector<GameObject*>> objects = scene->GetGameObjects();

			for (int y = 0; y < COLLIDER_LAYER; y++)
			{
				for (std::vector<GameObject*>::iterator iter = objects[y].begin();
					iter != objects[y].end();)
				{
					if ((*iter)->IsDeath() == true)
					{
						iter = objects[y].erase(iter);
						continue;
					}

					++iter;
				}
			}
		}
	}
}