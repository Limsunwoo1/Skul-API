#pragma once
#include "Common.h"
#include "Entity.h"
#include "Component.h"

namespace sw
{
	class Collider;
	class GameObject
	{
	public:
		GameObject();
		GameObject(Vector2 position);
		virtual ~GameObject();


		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		void SetPos(Vector2 pos) { mPos = pos; }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

		void AddComponent(Component* component);
		template <typename T>
		__forceinline T* AddComponent()
		{
			T* comp = new T();
			GameObject::AddComponent(comp);

			return comp;
		}

		template <typename T>
		__forceinline T* GetComponent()
		{
			T* component;

			for (Component* c : mComponents)
			{
				component = dynamic_cast<T*>(c);
				if (component != nullptr)
					return component;
			}

			return nullptr;
		}

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		bool IsDeath() { return mDeath; }
		void Deth() { mDeath = false; }

		eObjectState GetState() {return mCurstate;}
		void SetState(eObjectState state) { mCurstate = state;}

	private:
		std::vector<Component*> mComponents;
		Vector2D mPos;
		Vector2D mScale;

		bool mDeath;
		float mDeathTime;
		bool mDeathTimeOn;

		eObjectState mCurstate;
	};
}

