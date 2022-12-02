#pragma once
#include "GameObject.h"
#include "Shadow.h"

namespace sw
{
	class StateHandle;
	class Animator;
	class Image;
	class AttackCollider;
	class PlayerBase : public GameObject
	{
	public:
		PlayerBase();
		virtual ~PlayerBase();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void InitAnimtion() = 0;
		virtual void InitState() = 0;

		void ShadowEffect();

		void SetState(eObjectState type);
		StateHandle* GetStateHandle() { return mState; }

		eObjectState GetState();
		eObjectState GetPrevState();

		bool GetIsShadow() { return mbShadow; }
		void SetIsShadow(bool anable) { mbShadow = anable; }

		UINT GetMaxAttackCount() { return mMaxAttackCount; }

		void PushAttackCollider(AttackCollider* attackcollider) { mColliders.push_back(attackcollider); }
		AttackCollider* FindAttackCollider(std::wstring name);

		void SetParentObject(GameObject* parent) { mParentObject = parent; }
		GameObject* GetParent() { return mParentObject; }
	private:
		void CompleteEvent();

	protected:
		StateHandle* mState;
		Image* mImage;
		Animator* mAnimator;

		Shadow* mShaow;
		bool mbShadow;
		UINT mMaxAttackCount;

		std::vector<AttackCollider*> mColliders;
		GameObject* mParentObject;
	};
}

