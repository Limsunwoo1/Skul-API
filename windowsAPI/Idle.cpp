#include "Idle.h"
#include "Input.h"
#include "StateHandle.h"
#include "Jump.h"
#include "Sliding.h"
#include "Animator.h"
#include "Move.h"
#include "Attack.h"

namespace sw
{
	Idle::Idle()
	{

	}
	Idle::~Idle()
	{

	}
	void Idle::Start(PlayerBase* target)
	{
		SetTarget(target);

		SetStartAnimation();
		ResetCount();
	}

	void Idle::Run()
	{
		if (GetTarget() == nullptr)
			return;

		InputNextState();
	}
	void Idle::End()
	{

	}

	void Idle::ResetCount()
	{
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = dynamic_cast<Jump*>(stateHandle->GetState<Jump>(eObjectState::JUMP));
		if(jump != nullptr)
			jump->SetJumpCount(0);

		Sliding* sliding = dynamic_cast<Sliding*>(stateHandle->GetState<Sliding>(eObjectState::SLIDING));
		if (sliding != nullptr)
			sliding->SetSlidingCount(0);

		Attack* attack = dynamic_cast<Attack*>(stateHandle->GetState<Attack>(eObjectState::ATTACK));
		if (attack != nullptr)
			attack->SetAttackCount(0);
	}

	void Idle::InputNextState()
	{
		eObjectState NextState = eObjectState::END;

		if (KEY_PRESSE(eKeyCode::RIGHT) || KEY_PRESSE(eKeyCode::LEFT))
		{
			NextState = eObjectState::MOVE;
		}
		else if (KEY_DOWN(eKeyCode::C))
		{
			NextState = eObjectState::JUMP;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::ATTACK;
		}
		else if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
		}
		else if (KEY_DOWN(eKeyCode::SPACE))
		{

			NextState = eObjectState::SWITCH;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			
			NextState = eObjectState::SLIDING;
		}

		if (NextState != eObjectState::END)
		{
			End();
			GetTarget()->SetState(NextState);
		}
	}

	void Idle::SetStartAnimation()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		StateHandle* statehandle = GetTarget()->GetStateHandle();
		Move* move = statehandle->GetState<Move>(eObjectState::MOVE);

		if (move == nullptr)
		{
			animator->Play(GetR_Animation(), true);
			return;
		}
		// ���� ����
		if (!move->GetDirtion())
		{
			animator->Play(GetL_Animation(), true);
		}
		else if (move->GetDirtion())
		{
			animator->Play(GetR_Animation(), true);
		}
		else // ó�� ����� ������ ����
			animator->Play(GetR_Animation(), true);
	}
}