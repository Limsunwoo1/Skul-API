#include "SkulHeadItem.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Collider.h"

namespace sw
{
	SkulHeadItem::SkulHeadItem()
	{
		Initialize();
	}

	SkulHeadItem::~SkulHeadItem()
	{
	}

	void SkulHeadItem::Initialize()
	{
		SetScale(4.f, 4.f);
		// 애니메이터
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"SowrdSkulHead", L"..\\Resource\\Animation\\HeadUi\\SwordSkulHeadItem",Vector2(0.f, 10.f));
		animator->CreatAnimations(L"SamuraiHead", L"..\\Resource\\Animation\\HeadUi\\SamuraiHeadItem",Vector2(0.f, 10.f));

		animator->Play(L"SowrdSkulHead");
		// 리지드바디
		Rigidbody* rigidbody =AddComponent<Rigidbody>();
		rigidbody->SetOwner(this);
		rigidbody->SetGround(false);
		rigidbody->SetVelocity(Vector2(0.f, -700.f));

		// 콜리더
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(40.f, 40.f);
	}

	void SkulHeadItem::Tick()
	{
		GameObject::Tick();
	}

	void SkulHeadItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SkulHeadItem::OnCollisionEnter(Collider* other)
	{
	}

	void SkulHeadItem::OnCollisionStay(Collider* other)
	{
		if (!GetComponent<Rigidbody>()->GetGround())
			return;
	}

	void SkulHeadItem::OnCollisionExit(Collider* other)
	{
	}
}
