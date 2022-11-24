#include "Idle.h"
#include "Input.h"
#include "StateHandle.h"
#include "Jump.h"
#include "Sliding.h"

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

		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);
		jump->SetJumpCount(0);

		Sliding* sliding = stateHandle->GetState<Sliding>(eObjectState::SLIDING);
		sliding->SetSlidingCount(0);

		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			NextState = eObjectState::RIGHT;
		}
		else if (KEY_PRESSE(eKeyCode::LEFT))
		{
			NextState = eObjectState::LEFT;
		}
		else if (KEY_DOWN(eKeyCode::C))
		{
			NextState = eObjectState::JUMP;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::ATTACK_1;
		}
		else if (KEY_DOWN(eKeyCode::Z))
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