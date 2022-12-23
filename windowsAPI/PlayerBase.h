#pragma once
#include "GameObject.h"

using namespace std;


namespace sw
{
	class Shadow;
	class StateHandle;
	class Animator;
	class Image;
	class ObjectProjecTile;

	enum class eSkilType
	{
		Switch,
		SkilA,
		SkilB,
		End,
	};
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
		virtual void InitSkils() = 0;

		virtual void SwitchSkill(){};
		virtual void OnSkilA() {};
		virtual void OnSkilB() {};
		virtual void DashSmoke();
		virtual void JumpSmoke();
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

		void SetSildingDirction(bool dir) { mSlidingDirction = dir; }
		bool GetSildingDirction() { return mSlidingDirction; }

		ObjectProjecTile* GetProjecTile(eSkilType type) { return mSkils[(int)type]; }

		virtual void SwitchProjecTile(GameObject* other){};
	protected:
		StateHandle* mState;
		Image* mImage;
		Animator* mAnimator;

		vector<ObjectProjecTile*> mSkils;
		vector<pair<wstring, Box>> mColliders;
		GameObject* mParentObject;

		Box mColliderBox;
		UINT mMaxAttackCount;

		std::vector<Shadow*> mShadows;
		bool mbShadow;
		bool mSlidingDirction;
	};
}

