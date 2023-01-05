#pragma once
#include "Common.h"
#include "BossMonster.h"
#include "GenericAnimator.h"
#include "KingObject.h"
namespace sw
{
	class LeianaBoss;
	class LeianaBossRight;
	class Scene;
	class MainPlayer;
	class StaticObject;
	class Panel;
	class HpBar;
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

		void SetHp(float hp) { mHp = hp; }
		float GetHp() { return mHp; }

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
		void ChangeBossScene();
	private:
		LeianaBoss* mLeft;
		LeianaBossRight* mRight;
		StaticObject* mEnddingBack;
		StaticObject* mMidKing;
		KingObject* mKing;

		Panel* mHpPanel;
		HpBar* mHpBar;

		eBossPatton mCurPatton;
		eBossPatton mPrevePatton;
		float mDelta;
		float mDelay;

		bool mPatternProgress;
		bool mCombeMode;
		bool mModeChange;
		bool mBossSceneEnd;

		bool mEnddingSound;
		float mPattonCount;
		MainPlayer* mPlayer;

		float mHp;
		UINT mPower;

		GenericAnimator MyGenericAnimator;
	};
}

