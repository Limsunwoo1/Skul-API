#pragma once
#include "Common.h"

namespace sw
{
	class Component;
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
		void SetPos(float x, float y) { mPos = Vector2(x, y); }
		Vector2 GetPos() { return mPos; }
		void SetScale(Vector2 scale) { mScale = scale; }
		void SetScale(float x, float y) { mScale = Vector2(x, y); }
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

		template <typename T>
		__forceinline void DeleteComponent()
		{
			T* component;

			std::vector<Component*>::iterator iter;
			iter = mComponents.begin();

			for (; iter != mComponents.end();)
			{
				component = dynamic_cast<T*>(*iter);
				if (component != nullptr)
				{
					mComponents.erase(iter);

					int a = 0;
					return;
				}
				++iter;
			}

			return;
		}

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void OnCollisionEnter();
		virtual void OnCollisionStay();
		virtual void OnCollisionExit();

		bool IsDeath() { return mDeath; }
		void SetDeath(bool isdeath) { mDeath = isdeath; }

		ePlayerState GetState() {return mCurstate;}
		void SetState(ePlayerState state) { mCurstate = state;}

		void SetHp(UINT hp) { mHp = hp; }
		float GetHp() { return (float)mHp; }

		void SetPower(UINT power) { mPower = power; }
		UINT GetPower() { return mPower; }

	private:
		std::vector<Component*> mComponents;
		Vector2D mPos;
		Vector2D mScale;

		bool mDeath;
		float mDeathTime;
		bool mDeathTimeOn;

		int mHp;
		UINT mPower;
		ePlayerState mCurstate;
	};
}

