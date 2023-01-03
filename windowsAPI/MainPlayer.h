#pragma once
#include "GameObject.h"

namespace sw
{
	class PlayerBase;
	class Collider;
	class Rigidbody;
	class UiBase;
	class MainPlayer : public GameObject
	{
	public:
		MainPlayer();
		~MainPlayer();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void CheckGround();

		void KEY_DOWN_SPACE();
		void Reset();
		void SwitchPlayer();

		void SetPlayer(PlayerBase* player);
		PlayerBase* GetPlayer() { return mCurPlayer; }
		PlayerBase* GetNextPlayer() { return mNextPlayer; }

		void SetPlayerSwitch(bool change) { bPlayerSwitch = change; }
		bool GetPlayerSwitch() { return bPlayerSwitch; }

		void SetHeadParent(UiBase* ui) { mHeadParent = ui; }
		void SetSkilAHeadParent(UiBase* ui) { mSkilAParent = ui; }
		void SetSkilBHeadParent(UiBase* ui) { mSkilBParent = ui; }

	private:
		PlayerBase* mCurPlayer;
		PlayerBase* mNextPlayer;

		Rigidbody* mRigidbody;
		Collider* mCollider;

		bool bPlayerSwitch;

		UiBase* mHeadParent;
		UiBase* mSkilAParent;
		UiBase* mSkilBParent;
	};
}

