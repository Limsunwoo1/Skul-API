#include "Jump.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"
#include "Input.h"

namespace sw
{
	Jump::Jump()
		: mJumpCount(0)
	{
		
	}

	Jump::~Jump()
	{
		
	}

	void Jump::Start(PlayerBase* target)
	{
		++mJumpCount;
		SetTarget(target);

		if (mJumpCount > 2)
			return;

		SetStartAnimation();
	}

	void Jump::Run()
	{
		if (GetTarget() == nullptr)
			return;

		ChangeDrop();
		PresseInput();
		DownInput();
	}

	void Jump::End()
	{

	}

	void Jump::SetStartAnimation()
	{
		PlayerBase* player = GetTarget();

		// 점프력 설정
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = -700.f;
		rigidbody->SetVelocity(velocity);
		rigidbody->SetGround(false);


		// 방향설정
		bool state = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!state)
			animator->Play(GetL_Animation(), false);
		else if (state)
			animator->Play(GetR_Animation(), false);
	}

	void Jump::PresseInput()
	{
		PlayerBase* player = GetTarget();
		StateHandle* statehandle = player->GetStateHandle();
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			statehandle->GetState<Move>(ePlayerState::MOVE)->SetDirtion(false);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-400.f, 0.0f));
		}
		else if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			statehandle->GetState<Move>(ePlayerState::MOVE)->SetDirtion(true);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(400.f, 0.0f));
		}
	}

	void Jump::DownInput()
	{
		ePlayerState NextState = ePlayerState::END;
		if (KEY_DOWN(eKeyCode::C))
		{
			NextState = ePlayerState::JUMP;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = ePlayerState::JUMPATTACK;
		}
		else if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = ePlayerState::SLIDING;
		}

		if (NextState != ePlayerState::END)
		{
			End();
			GetTarget()->SetState(NextState);
		}
	}

	void Jump::ChangeDrop()
	{
		PlayerBase* player = GetTarget();
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();

		if (velocity.y < 0)
			return;
		
		End();
		player->SetState(ePlayerState::DROP);
		
		//if (rigidbody->GetGround())
		//{
		//	End();
		//	player->SetState(eObjectState::IDLE);
		//	mJumpCount = 0;
		//	return;
		//}
	}

}