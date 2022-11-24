#pragma once
#include "State.h"

namespace sw
{
	class DoubleJump : public State
	{
	public:
		DoubleJump();
		~DoubleJump();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

	};
}

