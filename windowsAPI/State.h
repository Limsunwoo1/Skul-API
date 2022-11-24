#pragma once
#include "Common.h"
#include "Player.h"

namespace sw
{
	class State
	{
	public:
		State();
		virtual ~State();

		virtual void Start(Player* target) = 0;
		virtual void Run() = 0;
		virtual void End() = 0;

		void SetTarget(Player* target) { mTarget = target; }
		Player* GetTarget() { return mTarget; }
	private:
		Player* mTarget;
	};
}

