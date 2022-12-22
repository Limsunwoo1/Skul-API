#pragma once
#include "GameObject.h"
#include <random>

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
	class Ground;
	class MonsterBase : public GameObject
	{
	public:
		MonsterBase();
		~MonsterBase();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override{};
		virtual void OnCollisionExit(Collider* other) override{};

		virtual void OnCollisionEnter() override{};
		virtual void OnCollisionStay() override{};
		virtual void OnCollisionExit() override{};

		virtual void InitializeAnimation() = 0;
		virtual void InitializeBox() = 0;
		virtual void InitalizeCollider() = 0;

		virtual void IDLE();
		virtual void Attack();
		virtual void Move();
		virtual void Hit();
		virtual void Staring();

		void Branch();

		void SetState(eMonsterState type) { mCurState = type; }
		eMonsterState GetState() { return mCurState; }

		void SetDirction(bool dir) { mDirction = dir; }
		bool GetDirction() { return mDirction; }

		void SetAble(eMonsterState type, bool able) { mState[(int)type] = able; }

		void SetDelta(float delta) { mDelta = delta; }
		bool GetSuperArmer() { return mArmer; }

		void CheckGround();

		bool GetHold() { return mHold; }
		void SetHold(bool hold) { mHold = hold; }
		void Hold();

		bool GetHiting() { return mHiting; }
		void SetHiting(bool hit) { mHiting = hit; }

		GameObject* GetTarget() { return mTarget; }
		void SetTarget(GameObject* object) { mTarget = object; }

	protected:
		Image* mImage;
		Animator* mAnimator;
		GameObject* mTarget;
		Ground* mGround;

		eMonsterState mCurState;
		eMonsterState mPrevState;
		float mDelta;
		float mMaxDelta;
		float mAttackCooltime;
		float mAttackCooltimeMax;
		float mDelay;
		float mDistance;
		float mStaringTime;

		int mMovement;
		Vector2 mPrevPos;
		Box mAttackcollider;
		Box mStaringCollider;

		std::wstring RName;
		std::wstring LName;

		bool mState[(int)eMonsterState::END];
		bool mDirction;
		bool mArmer;
		bool mStaring;
		bool mHold;
		bool mHiting;

		UINT32 mAttackX;
		UINT32 mAttackY;

		std::mt19937 rgen;
		std::uniform_int_distribution<int> rDelay;
		std::uniform_int_distribution<int> rDistance;
	};
}