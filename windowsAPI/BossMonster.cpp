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
		, mDirPos(true)
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
		case eBossPatton::Patton5:
		{
			Patton5();
		}
		break;
		case eBossPatton::Patton6:
		{
			Patton6();
		}
		break;
		case eBossPatton::Patton7:
		{
			Patton7();
		}
		break;
		case eBossPatton::Patton8:
		{
			Patton8();
		}
		break;
		case eBossPatton::Patton9:
		{
			Patton9();
		}
		case eBossPatton::Patton10:
		{
			Patton10();
		}
		break;
		}
	}
}
