#include "Item.h"
#include "Collider.h"
#include "Animator.h"

namespace sw
{
	Item::Item()
		: mMonsterCount(0)
		, mbDeactivate(true)
	{
		SetScale(3.0f, 3.0f);
		Initialize();
	}
	Item::~Item()
	{
	}
	void Item::Tick()
	{
		GameObject::Tick();
	}
	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Item::Initialize()
	{
		/*Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);

		animator->CreatAnimations(L"Deactivate", L"..\\");
		animator->CreatAnimations(L"Activate", L"..\\");

		animator->Play(L"Deactivate");*/

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(200.f, 200.f);
	}

	void Item::OnCollisionEnter(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
	void Item::OnCollisionStay(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
	void Item::OnCollisionExit(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
}