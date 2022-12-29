#include "BossMonster.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
namespace sw
{
	BossMonster::BossMonster()
		: mCurPatton(eBossPatton::Idle)
		, mNextPatton(eBossPatton::Idle)
		, mPattonState(ePattonState::NONE)
		, mDelta(0.0f)
		, mDelay(0.0f)
		, mDirction(true)
	{
		for (int i = (int)eBossPatton::Idle; i < (int)eBossPatton::End; ++i)
		{
			mPattonList.push_back(false);
		}
	}
	BossMonster::~BossMonster()
	{
		GameObject::~GameObject();
	}

	void BossMonster::InitializeAnimation()
	{
		
	}
	void BossMonster::InitalizeCollider()
	{
		
	}
	void BossMonster::Branch()
	{
		switch (mCurPatton)
		{
		case eBossPatton::Idle :
		{
			Idle();
		}
		break;
		case eBossPatton::Patton1:
		{
			Patton1();
		}
		break;
		case eBossPatton::Patton2:
		{
			Patton2();
		}
		break;
		case eBossPatton::Patton3:
		{
			Patton3();
		}
		break;
		case eBossPatton::Patton4:
		{
			Patton4();
		}
		break;
		}
	}
}
