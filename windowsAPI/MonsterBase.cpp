#include "MonsterBase.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "EventManager.h"

#include "Image.h"
#include "Collider.h"
#include "Animator.h"

namespace sw
{
	MonsterBase::MonsterBase()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mTarget(nullptr)
		, mCurState(eMonsterState::IDLE)
		, mPrevState(mCurState)
		, mDirction(true)
		, mColCount(0)

	{
		for (int i = 0; i < (int)eMonsterState::END; ++i)
		{
			mState[i] = false;
		}
		mState[(int)eMonsterState::IDLE] = true;
	}
	MonsterBase::~MonsterBase()
	{
		GameObject::~GameObject();
	}

	void MonsterBase::Tick()
	{
		GameObject::Tick();
	}

	void MonsterBase::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		GameObject::Render(hdc);
	}

	void MonsterBase::OnCollisionEnter(Collider* other)
	{
	}
	void MonsterBase::OnCollisionStay(Collider* other)
	{

	}
	void MonsterBase::OnCollisionExit(Collider* other)
	{

	}

	void MonsterBase::OnCollisionEnter()
	{
	}
	void MonsterBase::OnCollisionStay()
	{

	}
	void MonsterBase::OnCollisionExit()
	{

	}
	void MonsterBase::IDLE()
	{
	}
	void MonsterBase::Attack()
	{
	}
	void MonsterBase::MOVE()
	{
	}
	void MonsterBase::HIT()
	{
	}
}
