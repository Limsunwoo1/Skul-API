#pragma once
#include "State.h"

namespace sw
{
	class SkilB : public State
	{
	public:
		SkilB();
		~SkilB();

		virtual void Start(PlayerBase* target) override;
		virtual void Run() override;
		virtual void End() override;

	private:

	};
}

