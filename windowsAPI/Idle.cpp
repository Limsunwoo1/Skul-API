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
	void Idle::Start(Player* target)
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
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);
		jump->SetJumpCount(0);

		Sliding* sliding = stateHandle->GetState<Sliding>(eObjectState::SLIDING);
		sliding->SetSlidingCount(0);

		Attack* attack = stateHandle->GetState<Attack>(eObjectState::ATTACK);
		attack->SetAttackCount(0);
	}

	void Idle::InputNextState()
	{
		eObjectState NextState = eObjectState::END;

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
			NextState = eObjectState::ATTACK;
		}
		else if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
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
		Move* move = statehandle->GetState<Move>(eObjectState::LEFT);

		// ���� ����
		if (move->GetDirtion() == eObjectState::LEFT)
		{
			animator->Play(L"L_IDLE", true);
		}
		else if (move->GetDirtion() == eObjectState::RIGHT)
		{
			animator->Play(L"R_IDLE", true);
		}
		else // ó�� ����� ������ ����
			animator->Play(L"R_IDLE", true);
	}
}