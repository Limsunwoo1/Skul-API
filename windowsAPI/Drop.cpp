#include "Drop.h"
#include "Rigidbody.h"
#include "Input.h"
#include "StateHandle.h"
#include "Move.h"
#include "Jump.h"
#include "Animator.h"
#include "Sliding.h"


namespace sw
{
	Drop::Drop()
	{
	}
	Drop::~Drop()
	{
	}
	void Drop::Start(PlayerBase* target)
	{
		SetTarget(target);
		// 애니메이션 세팅해주는 세팅
		SetStartAnimation();
	}
	void Drop::Run()
	{
		SetAnimation();
		NextStateInput();
	}
	void Drop::End()
	{

	}
	void Drop::SetAnimation()
	{
		PlayerBase* player = GetTarget();
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		StateHandle* statehandle = player->GetStateHandle();

		if (rigidbody->GetGround())
		{
			End();
			player->SetState(eObjectState::IDLE);
			return;
		}

		Animator* animator = GetTarget()->GetComponent<Animator>();
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			statehandle->GetState<Move>(eObjectState::MOVE)->SetDirtion(false);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-400.f, 0.0f));

			animator->Play(GetL_Animation(), false);

		}
		else if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			statehandle->GetState<Move>(eObjectState::MOVE)->SetDirtion(true);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(400.f, 0.0f));

			animator->Play(GetR_Animation(), false);
		}
	}
	void Drop::SetStartAnimation()
	{
		PlayerBase* player = GetTarget();
		bool state = player->GetStateHandle()->GetState<Move>(eObjectState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!state)
			animator->Play(GetL_Animation(), false);
		else if (state)
			animator->Play(GetR_Animation(), false);
	}
	void Drop::NextStateInput()
	{
		PlayerBase* player = GetTarget();
		StateHandle* statehandle = player->GetStateHandle();
		Jump* jump = statehandle->GetState<Jump>(eObjectState::JUMP);
		Sliding* sliding = statehandle->GetState<Sliding>(eObjectState::SLIDING);

		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				End();
				player->SetState(eObjectState::JUMP);
			}
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			if (sliding->GetSlidingCount() < 2)
			{
				End();
				player->SetState(eObjectState::SLIDING);
			}
		}
	}
}