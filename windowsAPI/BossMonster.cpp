#include "BossMonster.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
namespace sw
{
	BossMonster::BossMonster()
		: mCurPatton(eBossPatton::Idle)
		, mNextPatton(eBossPatton::Idle)
		, mDelta(0.0f)
		, mDelay(0.0f)
	{
		InitializeAnimation();
		InitalizeCollider();
		SetScale(Vector2(4.f, 4.f));
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
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(80.f, 80.f));
	}
}
