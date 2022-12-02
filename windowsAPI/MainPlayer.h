#pragma once
#include "GameObject.h"

namespace sw
{
	class PlayerBase;
	class Collider;
	class Rigidbody;
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

		void Reset();
		void SwitchPlayer();

		void SetPlayer(PlayerBase* player);
		PlayerBase* GetPlayer() { return mCurPlayer; }
		PlayerBase* GetNextPlayer() { return mNextPlayer; }

		void SetPlayerSwitch(bool change) { bPlayerSwitch = change; }
		bool GetPlayerSwitch() { return bPlayerSwitch; }
	private:
		PlayerBase* mCurPlayer;
		PlayerBase* mNextPlayer;

		Rigidbody* mRigidbody;
		Collider* mCollider;

		bool bPlayerSwitch;
	};
}

