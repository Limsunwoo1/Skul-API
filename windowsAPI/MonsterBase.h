#pragma once
#include "GameObject.h"

namespace sw
{
	enum class eMonsterState
	{
		IDLE,
		MOVE,
		ATTACK,
		HIT,
		END
	};

	class Image;
	class Animator;
	class MonsterBase : public GameObject
	{
	public:
		MonsterBase();
		~MonsterBase();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		virtual void OnCollisionExit() override;

		virtual void IDLE();
		virtual void Attack();
		virtual void MOVE();
		virtual void HIT();

		void SetState(eMonsterState type) { mCurState = type; }
		eMonsterState GetState() { return mCurState; }

		void SetDirction(bool dir) { mDirction = dir; }
		bool GetDirction() { return mDirction; }

		void SetAble(eMonsterState type, bool able) { mState[(int)type] = able; }

	protected:
		Image* mImage;
		Animator* mAnimator;
		GameObject* mTarget;

		eMonsterState mCurState;
		eMonsterState mPrevState;
		float mDelta;
		float mMaxDelta;

		Box mAttackcollider;
		Box mStaring;

		bool mState[(int)eMonsterState::END];
		bool mDirction;
	};
}