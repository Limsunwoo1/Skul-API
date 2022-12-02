#pragma once
#include "State.h"
#include "Animator.h"

namespace sw
{
	class Switch : public State
	{
	public:
		Switch();
		~Switch();

		virtual void Start(PlayerBase* target) override;
		virtual void Run()override;
		virtual void End() override;

	private:
		bool mSwitch;
		sw::Animator::Event mSwitchSkill;
	};
}


