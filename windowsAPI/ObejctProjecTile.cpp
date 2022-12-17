#include "ObejctProjecTile.h"
#include "Animator.h"
#include "Collider.h"
#include "Time.h"
#include "UtilLog.h"
namespace sw
{
	ObejctProjecTile::ObejctProjecTile()
		: GameObject()
		, mTarget(nullptr)
		, mDelta(0.0f)
		, mReuse_Time(0.2f)
		, mAble(false)
	{
		SetDeath(true);
		Initialize();
	}
	ObejctProjecTile::~ObejctProjecTile()
	{
	}

	void ObejctProjecTile::Tick()
	{
		if (IsDeath())
			return;

		if (mTarget)
			SetPos(mTarget->GetPos());

		if (mAble)
			mDelta += Time::GetInstance()->DeltaTime();

		GameObject::Tick();
	}
	void ObejctProjecTile::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		if (mTarget)
			SetPos(mTarget->GetPos());

		GameObject::Render(hdc);
	}
	void ObejctProjecTile::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
	}
	void ObejctProjecTile::OnCollisionEnter(Collider* other)
	{
		if (mAble)
			return;

		mAble = true;

		GameObject* object = other->GetOwner();
		if (Event)
		{
			LOG("프로젝타일 충돌엔터");
			Event(object);
		}
		// hp감소
	}
	void ObejctProjecTile::OnCollisionStay(Collider* other)
	{
		LOG(STRING("델타 %f", mDelta));
		if (mDelta > mReuse_Time)
		{
			GameObject* object = other->GetOwner();
			if (Event)
			{
				LOG("프로젝타일 충돌스테이");
				Event(object);
			}
			// hp감소
			mDelta = 0.0f;
		}
	}
	void ObejctProjecTile::OnCollisionExit(Collider* other)
	{
		LOG("프로젝타일 충돌엔드");
		mAble = false;
		mDelta = 0.0f;
	}
	void ObejctProjecTile::SetEvent(const TColliderEvent& event)
	{
		Event = event;
	}
}