#pragma once
#include "GameObject.h"
#include "Shadow.h"

namespace sw
{
	class StateHandle;
	class Animator;
	class Image;
	class Player : public GameObject
	{
	public:
		Player();
		virtual ~Player();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void ShadowEffect();

		void SetState(eObjectState type);
		StateHandle* GetStateHandle() { return mState; }

		eObjectState GetState();
		eObjectState GetPrevState();

		bool GetIsShadow() { return mbShadow; }
		void SetIsShadow(bool anable) { mbShadow = anable; }

		UINT GetMaxAttackCount() { return mMaxAttackCount; }
	private:
		void CompleteEvent();

	private:
		Image* mImage;
		Animator* mAnimator;
		StateHandle* mState;
		
		Shadow* mShaow;
		bool mbShadow;

		float mSpeed;
		UINT mMaxAttackCount;
	};
}

