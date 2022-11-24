#pragma once
#include "GameObject.h"

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

		void SetState(eObjectState type);
		StateHandle* GetStateHandle() { return mState; }
		eObjectState GetState();
		eObjectState GetPrevState();
	private:
		void CompleteEvent();

	private:
		float mSpeed;
		Image* mImage;
		Animator* mAnimator;
		
		StateHandle* mState;
	};
}

