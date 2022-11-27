#pragma once
#include "State.h"

namespace sw
{
	class Idle : public State
	{
	public:
		Idle();
		~Idle();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

		void ResetCount();
		void SetStartAnimation();
		void InputNextState();
	};
}

