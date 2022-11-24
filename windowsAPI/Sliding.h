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
	private:
		eObjectState mDirtion;

		float mDelta;
		float mRuntime;
		float mForce;
		float mDelay;
		bool bSliding;
	};
}

