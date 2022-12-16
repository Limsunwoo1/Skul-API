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

		virtual void OnCollisionEnter(Collider* other) override{};
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

		UINT32 GetColCount() { return mColCount; }
		void SetColCount(UINT32 count) { mColCount = count; }

		void SetDelta(float delta) { mDelta = delta; }
		bool GetSuperArmer() { return mArmer; }

		void CheckGround();

	protected:
		Image* mImage;
		Animator* mAnimator;
		GameObject* mTarget;
		UINT32 mColCount;

		eMonsterState mCurState;
		eMonsterState mPrevState;
		float mDelta;
		float mMaxDelta;

		Box mAttackcollider;
		Box mStaring;

		std::wstring RName;
		std::wstring LName;

		bool mState[(int)eMonsterState::END];
		bool mDirction;
		bool mArmer;

		UINT32 mAttackX;
		UINT32 mAttackY;
	};
}