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
	class HUD;
	class UiBase;
	class Scene;
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
		virtual void InitMyObject() {};
		virtual void DeleteMyobject() {};
		virtual void InitMyObject(Scene* scene) {};
		virtual void DeleteMyobject(Scene* scene) {};

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

		virtual void SwitchProjecTile(GameObject* object){};
		virtual void SkilAProjecTile(GameObject* object) {};
		virtual void SkilBProjecTile(GameObject* object) {};

		UiBase* GetHeadImage() { return (UiBase*)mHeadImage; }
		UiBase* GetSKilAImage() { return (UiBase*)mSkilAImage; }
		UiBase* GetSKilBImage() { return (UiBase*)mSkilBImage; }
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

		HUD* mHeadImage;
		HUD* mSkilAImage;
		HUD* mSkilBImage;
	};
}

