#include "ProjectObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Time.h"
namespace sw
{
	ProjectObject::ProjectObject()
		: GameObject()
		, mTarget(nullptr)
		, mDelta(0.0f)
		, mReuse_Time(0.2f)
		, mAble(false)
	{
		SetDeath(true);
		Initialize();
	}
	ProjectObject::~ProjectObject()
	{
	}

	void ProjectObject::Tick()
	{
		if (IsDeath())
			return;

		if (mAble)
			mDelta = Time::GetInstance()->DeltaTime();

		GameObject::Tick();
	}
	void ProjectObject::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		GameObject::Render(hdc);
	}
	void ProjectObject::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
	}
	void ProjectObject::OnCollisionEnter(Collider* other)
	{
		if (mAble)
			return;

		mAble = true;

		GameObject* object = other->GetOwner();
		if(Event)
			Event(object);
		// hp감소
	}
	void ProjectObject::OnCollisionStay(Collider* other)
	{
		if (mDelta > mReuse_Time)
		{
			GameObject* object = other->GetOwner();
			if(Event)
				Event(object);
			// hp감소
			mDelta = 0.0f;
		}
	}
	void ProjectObject::OnCollisionExit(Collider* other)
	{
		mAble = false;
		mDelta = 0.0f;
	}
	void ProjectObject::SetEvent(const TColliderEvent& event)
	{
		Event = event;
	}
}