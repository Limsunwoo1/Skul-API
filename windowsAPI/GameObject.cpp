#include "GameObject.h"
#include "Component.h"

namespace sw
{
	GameObject::GameObject()
		: mPos {0.0f, 0.0f}
		, mScale {1.0f, 1.0f}
		, mDeath (false)
		, mDeathTime(-100.0f)
		, mDeathTimeOn(false)
	{
	}

	GameObject::GameObject(Vector2 position)
		: mPos{ position }
		, mScale{ 1.0f, 1.0f }
		, mDeath(false)
		, mDeathTime(-100.0f)
		, mDeathTimeOn(false)
	{

	}

	GameObject::~GameObject()
	{
		for (Component* com : mComponents)
		{
			if (!com)
				continue;

			delete com;
			com = nullptr;
		}
	}

	void GameObject::Initialize()
	{
	}

	void GameObject::Tick()
	{
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Tick();
		}
	}

	void GameObject::Render(HDC hdc)
	{
		// 모든 컴포넌트를 Render 호출
		for (Component* component : mComponents)
		{
			if (component == nullptr)
				continue;

			component->Render(hdc);
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		if (component == nullptr)
			return;

		mComponents.push_back(component);
		component->mOwner = this;
	}
	void GameObject::OnCollisionEnter(Collider* other)
	{
	}
	void GameObject::OnCollisionStay(Collider* other)
	{
	}
	void GameObject::OnCollisionExit(Collider* other)
	{
	}
}
