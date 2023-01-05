#pragma once
#include "Common.h"
#include "BossMonster.h"
#include "GenericAnimator.h"
namespace sw
{
	class LeianaBoss;
	class LeianaBossRight;
	class Scene;
	class MainPlayer;
	class StaticObject;
	class LeianaControler
	{
	public:
		LeianaControler();
		~LeianaControler();

		void Tick();
		void Initialize();

		LeianaBoss* GetLeftLeiana() { return mLeft; }
		LeianaBossRight* GetRightLeiana() { return mRight; }

		MainPlayer* GetPlayer() { return mPlayer; }
		void SetPlayer(MainPlayer* player);

		float GetDelta() { return mDelta; }
		void SetDelta(float delta) { mDelta = delta; }

		float GetDelay() { return mDelay; }
		void SetDelay(float delay) { mDelay = delay; }

		eBossPatton GetCurPatton() { return mCurPatton; }
		void SetCurPatton(eBossPatton type);

		bool GetPatternProgress() {return mPatternProgress;}
		void SetPatternProgress(bool on) { mPatternProgress = on; }

		bool GetCombeMode() { return mCombeMode; }
		void SetCombeMode(bool on) { mCombeMode = on; }

		void SetHp(UINT hp) { mHp = hp; }
		UINT GetHp() { return mHp; }

		void SetPower(UINT power) { mPower = power; }
		UINT GetPower() { return mPower; }

		int GetPattonCount() { return mPattonCount; }

		void Brunch();
		void Idle();
		void Patton1();
		void Patton2();
		void Patton3();
		void Patton4();
		void Patton5();
		void Patton6();
		void Patton7();
		void Patton8();
		void Patton9();
		void Patton10();

		void ReSetDirPos();
		void PushBoss(Scene* scene);

		void OuttroIn();
		void OuttroOut();
	private:
		LeianaBoss* mLeft;
		LeianaBossRight* mRight;
		StaticObject* mEnddingBack;
		StaticObject* mMidKing;
		eBossPatton mCurPatton;
		eBossPatton mPrevePatton;
		float mDelta;
		float mDelay;

		bool mPatternProgress;
		bool mCombeMode;
		bool mModeChange;
		bool mBossSceneEnd;

		float mPattonCount;
		MainPlayer* mPlayer;

		UINT mHp;
		UINT mPower;

		GenericAnimator MyGenericAnimator;
	};
}

