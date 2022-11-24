#pragma once
#include "Common.h"
#include "Entity.h"

namespace sw
{
	class GameObject;
	class Scene : public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void Enter();
		virtual void Exit();

		void AddGameObject(GameObject* object, eColliderLayer type);
		void DeleteGameObject(GameObject* object, eColliderLayer type);

		std::vector<GameObject*>& GetGameObject(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<std::vector<GameObject*>>& GetGameObjects() { return mObjects; }

		virtual void Release();

	private:
		std::vector<std::vector<GameObject*>> mObjects;
	};
}
