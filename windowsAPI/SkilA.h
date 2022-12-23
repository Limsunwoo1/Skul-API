#pragma once
#include "State.h"

namespace sw
{
	class SkilA : public State
	{
	public:
		SkilA();
		~SkilA();

		virtual void Start(PlayerBase* target) override;
		virtual void Run() override;
		virtual void End() override;

	private:

	};
}

