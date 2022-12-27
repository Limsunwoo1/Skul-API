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
		, mNotMove(false)
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

	
		if (mTarget && !mNotMove)
			SetPos(mTarget->GetPos() + mOffeset);

		for (auto iter = mColiedList.begin(); iter != mColiedList.end(); ++iter)
		{
			iter->second += Time::GetInstance()->DeltaTime();
		}
		

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
		if (mStartOffset > 0.0f)
			return;
		auto iter = mColiedList.find(other->GetID());
		if(iter == mColiedList.end())
			mColiedList.insert(std::make_pair(other->GetID(), 0.0f));

		if (Event)
		{
			Event(other->GetOwner());
		}
		// hp°¨¼Ò
	}
	void ObjectProjecTile::OnCollisionStay(Collider* other)
	{
		auto iter = mColiedList.find(other->GetID());
		if (iter == mColiedList.end())
			return;
		LOG(STRING("ID %d", iter->first))
		LOG(STRING("Delta %f", iter->second))
		if (iter->second < mReuse_Time)
			return;

		if (Event)
		{
			Event(other->GetOwner());
		}

		iter->second = 0.0f;
	}
	void ObjectProjecTile::OnCollisionExit(Collider* other)
	{
		mAble = false;

		auto iter = mColiedList.find(other->GetID());
		if (iter != mColiedList.end())
			mColiedList.erase(iter);
	}
	void ObjectProjecTile::SetEvent(const TColliderEvent& event)
	{
		Event = event;
	}
}