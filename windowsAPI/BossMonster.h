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

		eBossPatton GetCurPatton() { return mCurPatton; }
		void SetCurPatton(eBossPatton patton) { mCurPatton = patton; }

		eBossPatton GetNextPatton() { return mNextPatton; }
		void SetNextPatton(eBossPatton patton) { mNextPatton = patton; }

		float GetDelta() { return mDelta; }
		void SetDelta(float delta) { mDelta = delta; }

		float GetDelay() { return mDelay; }
		void SetDelay(float delay) { mDelay = delay; }

	protected:
		std::vector<bool> mPattonList;
		eBossPatton mCurPatton;
		eBossPatton mNextPatton;

		float mDelta;
		float mDelay;

		UINT mHP;
	};
}