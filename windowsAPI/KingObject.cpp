#include "KingObject.h"
#include "Animator.h"
#include "Time.h"
namespace sw
{
	KingObject::KingObject()
	{
		Init();
		mEndding = false;
	}

	KingObject::~KingObject()
	{
		GameObject::~GameObject();
	}

	void KingObject::Tick()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		GameObject::Tick();

		if (mEndding)
			return;

		Animator* animator = GetComponent<Animator>();
		if (animator->GetCurAnimationName() == L"KingPose")
		{
			if (animator->isComplete())
			{
				animator->Play(L"KingIdle", true);
				mDelta = 0.0f;
			}
		}

		if (mDelta > 15.f)
		{
			animator->Play(L"KingPose");
			mDelta = 0.0f;
		}
	}

	void KingObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void KingObject::Init()
	{
		SetScale(4.f, 4.f);

		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"KingIdle", L"..\\Resource\\Animation\\2ChKing\\Idle",Vector2::Zero, 0.2f);
		animator->CreatAnimations(L"KingPose", L"..\\Resource\\Animation\\2ChKing\\Pose", Vector2::Zero, 0.1f);
		animator->CreatAnimations(L"KingSurprise", L"..\\Resource\\Animation\\2ChKing\\Surprise", Vector2::Zero, 0.2f);

		animator->Play(L"KingIdle",true);
	}
}