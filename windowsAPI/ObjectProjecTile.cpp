#include "ObjectProjecTile.h"
#include "Animator.h"
#include "Collider.h"
#include "Time.h"
#include "UtilLog.h"
#include "MonsterBase.h"
namespace sw
{
	ObjectProjecTile::ObjectProjecTile()
		: GameObject()
		, mTarget(nullptr)
		, mDelta(0.0f)
		, mReuse_Time(0.2f)
		, mAble(false)
		, mEffectName(L"")
		, mOffeset(Vector2::Zero)
		, mStartOffset(0.0f)
	{
		SetDeath(true);
		Initialize();
	}
	ObjectProjecTile::~ObjectProjecTile()
	{
	}

	void ObjectProjecTile::Tick()
	{
		if (IsDeath())
			return;

		mStartOffset -= Time::GetInstance()->DeltaTime();
		if (mStartOffset > 0.0f)
			return;

		if (mTarget)
			SetPos(mTarget->GetPos() + mOffeset);

		if (mAble)
			mDelta += Time::GetInstance()->DeltaTime();

		GameObject::Tick();
	}
	void ObjectProjecTile::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		if (mStartOffset > 0.0f)
			return;

		GameObject::Render(hdc);
	}
	void ObjectProjecTile::Initialize()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
	}
	void ObjectProjecTile::OnCollisionEnter(Collider* other)
	{
		if (mAble)
			return;

		if (mStartOffset > 0.0f)
			return;

		mAble = true;
		GameObject* object = other->GetOwner();
		MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
		if (monster)
		{
			eMonsterState type = monster->GetState();
			if (monster->GetSuperArmer())
			{
				monster->Hit();
			}
			else
			{
				monster->SetAble(type, false);
				monster->SetState(eMonsterState::HIT);
				monster->SetDelta(0.0f);
			}
		}

		if (Event)
		{
			Event(object);
		}
		// hp감소
	}
	void ObjectProjecTile::OnCollisionStay(Collider* other)
	{
		if (mDelta > mReuse_Time)
		{
			GameObject* object = other->GetOwner();
			MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
			if (monster)
			{
				eMonsterState type = monster->GetState();
				if (monster->GetSuperArmer())
				{
					monster->Hit();
				}
				else
				{
					monster->SetAble(type, false);
					monster->SetState(eMonsterState::HIT);
					monster->SetDelta(0.0f);
				}
			}
			if (Event)
			{
				Event(object);
			}
			// hp감소
			mDelta = 0.0f;
		}
	}
	void ObjectProjecTile::OnCollisionExit(Collider* other)
	{
		mAble = false;
		mDelta = 0.0f;
	}
	void ObjectProjecTile::SetEvent(const TColliderEvent& event)
	{
		Event = event;
	}
}