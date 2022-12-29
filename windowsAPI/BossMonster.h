#pragma once
#include "GameObject.h"
namespace sw
{
	enum class eBossPatton
	{
		Idle,
		Patton1,
		Patton2,
		Patton3,
		Patton4,
		End,
	};

	enum class ePattonState
	{
		NONE,
		READY,
		LANDING,
		END,
	};

	class MainPlayer;
	class BossMonster : public GameObject
	{
	public:
		BossMonster();
		~BossMonster();

		virtual void Tick() override{};
		virtual void Render(HDC hdc)override {};

		virtual void Initialize()override {};
		virtual void InitializeAnimation();
		virtual void InitalizeCollider();
		virtual void InitalizeProjecTile() {};

		virtual void Idle() {};
		virtual void Patton1(){};
		virtual void Patton2() {};
		virtual void Patton3() {};
		virtual void Patton4() {};

		virtual void Branch();

		virtual void Patton1_Stand_by(bool type = true) {}
		virtual void Patton1_Progress() {}
		virtual void Patton2_Stand_by( bool type = true) {}
		virtual void Patton2_Progress() {}
		virtual void Patton3_Stand_by( bool type = true) {}
		virtual void Patton3_Progress() {}
		virtual void Patton4_Stand_by( bool type = true) {}
		virtual void Patton4_Progress() {}

		eBossPatton GetCurPatton() { return mCurPatton; }
		void SetCurPatton(eBossPatton patton) { mCurPatton = patton; }

		eBossPatton GetNextPatton() { return mNextPatton; }
		void SetNextPatton(eBossPatton patton) { mNextPatton = patton; }

		ePattonState GetCurPattonState() { return mPattonState; }
		void SetCurPattonState(ePattonState type) { mPattonState = type; }

		float GetDelta() { return mDelta; }
		void SetDelta(float delta) { mDelta = delta; }

		float GetDelay() { return mDelay; }
		void SetDelay(float delay) { mDelay = delay; }

		MainPlayer* GetPlayer() { return mPlayer; }
		void SetPlayer(MainPlayer* player) { mPlayer = player; }

		bool GetDirction() { return mDirction; }
		void SetDirction(bool dir) { mDirction = dir; }
	protected:
		std::vector<bool> mPattonList;
		eBossPatton mCurPatton;
		eBossPatton mNextPatton;
		ePattonState mPattonState;

		float mDelta;
		float mDelay;

		MainPlayer* mPlayer;
		UINT mHP;

		bool mDirction;
	};
}