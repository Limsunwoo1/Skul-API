#pragma once
#include "Entity.h"
#include "Common.h"

namespace sw
{
	class GameObject;
	class Component : public Entity
	{
	public:
		friend class GameObject;

		Component(eComponentType type);
		Component() = delete;
		virtual ~Component();

		virtual void Tick() = 0;
		virtual void Render(HDC hdc);

		GameObject* GetOwner() { return mOwner; }
		void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		const eComponentType mType;
		GameObject* mOwner;
	};
}

