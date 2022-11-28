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

	void Jump::Start(Player* target)
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
		Player* player = GetTarget();

		// 점프력 설정
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = -700.f;
		rigidbody->SetVelocity(velocity);
		rigidbody->SetGround(false);


		// 방향설정
		eObjectState state = player->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (state == eObjectState::LEFT)
			animator->Play(GetL_Animation(), false);
		else if (state == eObjectState::RIGHT)
			animator->Play(GetR_Animation(), false);
	}

	void Jump::PresseInput()
	{
		Player* player = GetTarget();
		StateHandle* statehandle = player->GetStateHandle();
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::LEFT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-500.f, 0.0f));
		}
		else if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::RIGHT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(500.f, 0.0f));
		}
	}

	void Jump::DownInput()
	{
		eObjectState NextState = eObjectState::END;
		if (KEY_DOWN(eKeyCode::C))
		{
			NextState = eObjectState::JUMP;
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::JUMPATTACK;
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

	void Jump::ChangeDrop()
	{
		Player* player = GetTarget();
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();

		if (velocity.y < 0)
			return;
		
		End();
		player->SetState(eObjectState::DROP);
		
		//if (rigidbody->GetGround())
		//{
		//	End();
		//	player->SetState(eObjectState::IDLE);
		//	mJumpCount = 0;
		//	return;
		//}
	}

}