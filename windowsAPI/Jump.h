#pragma once
#include "State.h"

namespace sw
{
	class Jump: public State
	{
	public:
		Jump();
		~Jump();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;
	};
}

