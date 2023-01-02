#include "ObjectProjecTile.h"
#include "Animator.h"
#include "Collider.h"
#include "Time.h"
#include "UtilLog.h"
#include "MonsterBase.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "StateHandle.h"
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
		, mDirVec(Vector2::Zero)
		, mSpeed(0)
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
		
		if (mDirVec != Vector2::Zero)
		{
			Vector2 pos = GetPos();
			pos += mDirVec.Normalize() * Time::GetInstance()->DeltaTime() * mSpeed;
		}
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
		PlayerBase* player = dynamic_cast<PlayerBase*>(other->GetOwner());
		if (player != nullptr)
		{
			ePlayerState state = player->GetStateHandle()->GetStateType();
			if (state != ePlayerState::SLIDING)
			{
				int hp = other->GetOwner()->GetHp();
				int power = mTarget->GetPower();
				other->GetOwner()->SetHp(hp - power);
			}
			return;
		}

		int hp = other->GetOwner()->GetHp();
		int power = mTarget->GetPower();
		other->GetOwner()->SetHp(hp - power);
	}
	void ObjectProjecTile::OnCollisionStay(Collider* other)
	{
		auto iter = mColiedList.find(other->GetID());
		if (iter == mColiedList.end())
			return;

		if (iter->second < mReuse_Time)
			return;

		if (Event)
		{
			Event(other->GetOwner());
		}

		int hp = other->GetOwner()->GetHp();
		int power = mTarget->GetPower();
		other->GetOwner()->SetHp(hp - power);

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