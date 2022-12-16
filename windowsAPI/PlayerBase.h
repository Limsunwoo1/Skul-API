#pragma once
#include "GameObject.h"

using namespace std;


namespace sw
{
	class Shadow;
	class StateHandle;
	class Animator;
	class Image;
	class EffectObject;
	class ProjectObject;

	class PlayerBase : public GameObject
	{
	public:
		PlayerBase();
		virtual ~PlayerBase();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other){}
		virtual void OnCollisionStay(Collider* other){}
		virtual void OnCollisionExit(Collider* other){}

		virtual void InitAnimtion() = 0;
		virtual void InitState() = 0;
		virtual void InitAttackCollider() = 0;

		virtual void SwitchSkill(){};
		virtual void DashEffect(){};
		virtual void OnAttackEffect(GameObject* other){};

		void ShadowEffect(){};

		void SetState(ePlayerState type);
		StateHandle* GetStateHandle() { return mState; }

		ePlayerState GetState();
		ePlayerState GetPrevState();

		bool GetIsShadow() { return mbShadow; }
		void SetIsShadow(bool anable) { mbShadow = anable; }

		UINT GetMaxAttackCount() { return mMaxAttackCount; }

		void SetParentObject(GameObject* parent) { mParentObject = parent; }
		GameObject* GetParent() { return mParentObject; }

		void SetColliders(wstring key, Box box);
		const Box& GetColliders(wstring key) const;

		void SetColliderBox(Box box) { mColliderBox = box; }

		virtual void SwitchProject(GameObject* other){};
	protected:
		StateHandle* mState;
		Image* mImage;
		Animator* mAnimator;
		EffectObject* mEffect;
		ProjectObject* mSwitchProject;

		vector<pair<wstring, Box>> mColliders;
		GameObject* mParentObject;

		Box mColliderBox;
		UINT mMaxAttackCount;

		Shadow* mShaow;
		bool mbShadow;
	};
}

