#pragma once
#include "GameObject.h"
#include "Shadow.h"

using namespace std;

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
		virtual void InitAttackCollider() = 0;

		virtual void SwitchSkill();

		void ShadowEffect();

		void SetState(eObjectState type);
		StateHandle* GetStateHandle() { return mState; }

		eObjectState GetState();
		eObjectState GetPrevState();

		bool GetIsShadow() { return mbShadow; }
		void SetIsShadow(bool anable) { mbShadow = anable; }

		UINT GetMaxAttackCount() { return mMaxAttackCount; }

		void SetParentObject(GameObject* parent) { mParentObject = parent; }
		GameObject* GetParent() { return mParentObject; }

		void SetColliders(wstring key, Box box);
		const Box& GetColliders(wstring key) const;

		void SetColliderBox(Box box) { mColliderBox = box; }
	private:
		void CompleteEvent();

	protected:
		StateHandle* mState;
		Image* mImage;
		Animator* mAnimator;

		vector<pair<wstring, Box>> mColliders;
		GameObject* mParentObject;

		Box mColliderBox;
		UINT mMaxAttackCount;

		Shadow* mShaow;
		bool mbShadow;
	};
}
