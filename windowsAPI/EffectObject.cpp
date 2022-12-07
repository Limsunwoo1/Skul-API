#include "EffectObject.h"
#include "Collider.h"
#include "Camera.h"
#include "PlayerBase.h"
#include "Animator.h"

namespace sw
{
	EffectObject::EffectObject()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);
		SetDeath(true);
		if (mAnimator == nullptr)
		{
			mAnimator = AddComponent<Animator>();
			mAnimator->SetOwner(this);
		}
	}

	EffectObject::~EffectObject()
	{
		
	}

	void EffectObject::Tick()
	{
		if (IsDeath())
			return;

		if (mAnimator != nullptr)
		{
			if (mAnimator->bPlayAnimation() && mAnimator->isComplete())
				SetDeath(true);
		}

		GameObject::Tick();
	}

	void EffectObject::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		GameObject::Render(hdc);
	}
}