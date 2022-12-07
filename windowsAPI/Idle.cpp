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
		Jump* jump = dynamic_cast<Jump*>(stateHandle->GetState<Jump>(ePlayerState::JUMP));
		if(jump != nullptr)
			jump->SetJumpCount(0);

		Sliding* sliding = dynamic_cast<Sliding*>(stateHandle->GetState<Sliding>(ePlayerState::SLIDING));
		if (sliding != nullptr)
			sliding->SetSlidingCount(0);

		Attack* attack = dynamic_cast<Attack*>(stateHandle->GetState<Attack>(ePlayerState::ATTACK));
		if (attack != nullptr)
			attack->SetAttackCount(0);
	}

	void Idle::InputNextState()
	{
		ePlayerState NextState = ePlayerState::END;

		if (KEY_PRESSE(eKeyCode::RIGHT) || KEY_PRESSE(eKeyCode::LEFT))
		{
			NextState = ePlayerState::MOVE;
		}
		else if (KEY_DOWN(eKeyCode::C))
		{
			NextState = ePlayerState::JUMP;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = ePlayerState::ATTACK;
		}
		else if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = ePlayerState::SLIDING;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = ePlayerState::ATTACK;
		}

		if (NextState != ePlayerState::END)
		{
			End();
			GetTarget()->SetState(NextState);
		}
	}

	void Idle::SetStartAnimation()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		StateHandle* statehandle = GetTarget()->GetStateHandle();
		Move* move = statehandle->GetState<Move>(ePlayerState::MOVE);

		if (move == nullptr)
		{
			animator->Play(GetR_Animation(), true);
			return;
		}
		// 방향 설정
		if (!move->GetDirtion())
		{
			animator->Play(GetL_Animation(), true);
		}
		else if (move->GetDirtion())
		{
			animator->Play(GetR_Animation(), true);
		}
		else // 처음 실행시 오른쪽 방향
			animator->Play(GetR_Animation(), true);
	}
}