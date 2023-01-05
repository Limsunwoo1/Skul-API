#pragma once
#include "GameObject.h"
#include <random>
#include "HpBar.h"
#include "Panel.h"
#include "Sound.h"

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

		virtual void Branch();
		virtual void ProejcTielDelte() {};

		void OffSound();

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

		bool GetStraing() { return mStaring; }
		void SetStraing(bool staring) { mStaring = staring; }

		GameObject* GetTarget() { return mTarget; }
		void SetTarget(GameObject* object) { mTarget = object; }

		void PushUi();
		void InActive();
		void OnActive();

	protected:
		Image* mImage;
		Animator* mAnimator;
		GameObject* mTarget;
		Ground* mGround;
		
		Panel* mHpPanel;
		HpBar* mHpBar;

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
		bool mUiOn;

		UINT32 mAttackX;
		UINT32 mAttackY;

		std::mt19937 rgen;
		std::uniform_int_distribution<int> rDelay;
		std::uniform_int_distribution<int> rDistance;

		Sound mHitSound;
		Sound mAttackSound;
	};
}