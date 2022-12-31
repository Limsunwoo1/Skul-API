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
		Patton5,
		Patton6,
		Patton7,
		Patton8,
		Patton9,
		Patton10,
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
		virtual void Patton5() {};
		virtual void Patton6() {};
		virtual void Patton7() {};
		virtual void Patton8() {};
		virtual void Patton9() {};
		virtual void Patton10() {};

		virtual void Branch();

		virtual void Patton1_Stand_by(bool type = true) {}
		virtual void Patton1_Progress() {}
		virtual void Patton2_Stand_by( bool type = true) {}
		virtual void Patton2_Progress() {}
		virtual void Patton3_Stand_by( bool type = true) {}
		virtual void Patton3_Progress() {}
		virtual void Patton4_Stand_by( bool type = true) {}
		virtual void Patton4_Progress() {}
		virtual void Patton5_Stand_by(bool type = true) {}
		virtual void Patton5_Progress() {}
		virtual void Patton6_Stand_by(bool type = true) {}
		virtual void Patton6_Progress() {}
		virtual void Patton7_Stand_by(bool type = true) {}
		virtual void Patton7_Progress() {}
		virtual void Patton8_Stand_by(bool type = true) {}
		virtual void Patton8_Progress() {}
		virtual void Patton9_Stand_by(bool type = true) {}
		virtual void Patton9_Progress() {}
		virtual void Patton10_Stand_by(bool type = true) {}
		virtual void Patton10_Progress() {}

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

		bool GetDirPos() { return mDirPos; }
		void SetDirPos(bool dir) { mDirPos = dir; }
	protected:
		std::vector<bool> mPattonList;
		eBossPatton mCurPatton;
		eBossPatton mNextPatton;
		ePattonState mPattonState;

		float mDelta;
		float mDelay;

		MainPlayer* mPlayer;
		UINT mHP;

		// ¿À¸¥ÂÊ true ¿ÞÂÊ false
		bool mDirPos;
	};
}