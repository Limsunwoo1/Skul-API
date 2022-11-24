#include "Idle.h"
#include "Input.h"

namespace sw
{
	Idle::Idle()
	{

	}
	Idle::~Idle()
	{

	}
	void Idle::Start(Player* target)
	{
		SetTarget(target);
	}

	void Idle::Run()
	{
		eObjectState NextState = eObjectState::END;

		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			NextState = eObjectState::RIGHT;
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			NextState = eObjectState::LEFT;
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			NextState = eObjectState::JUMP;
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::ATTACK_1;
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
		}

		if (NextState != eObjectState::END)
		{
			End();
			GetTarget()->SetState(NextState);
		}
	}
	void Idle::End()
	{

	}
}