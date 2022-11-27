#pragma once
#include "State.h"

namespace sw
{
	class Sliding : public State
	{
	public:
		Sliding();
		~Sliding();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

		bool SlidingRun();
		bool DoubleSlide();
		void InputNextState();

		UINT GetSlidingCount() { return mSlidingCount; }
		void SetSlidingCount(UINT count) { mSlidingCount = count; }

		void SetStartAnimation();
	private:
		eObjectState mDirtion;

		float mDelta;
		float mRuntime;
		float mForce;
		float mDelay;

		bool bSliding;
		bool bInput;

		UINT mSlidingCount;

		eObjectState mInputState;
	};
}

