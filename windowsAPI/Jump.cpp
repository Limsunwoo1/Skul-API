#include "Jump.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"
#include "Input.h"

namespace sw
{
	Jump::Jump()
	{
		
	}

	Jump::~Jump()
	{
		
	}

	void Jump::Start(Player* target)
	{
		SetTarget(target);
		Rigidbody* rigidbody = target->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = -700.f;
		rigidbody->SetVelocity(velocity);
		rigidbody->SetGround(false);
	}

	void Jump::Run()
	{
		Player* player = GetTarget();
		if (player == nullptr)
			return;

		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		if (rigidbody->GetGround())
		{
			End();
			player->SetState(eObjectState::IDLE);
			return;
		}

		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		StateHandle* stathandle = player->GetStateHandle();

		eObjectState NextState = eObjectState::END;
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			stathandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::LEFT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-300.f, 0.0f));
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			stathandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::RIGHT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(300.f, 0.0f));
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			NextState = eObjectState::DOUBLEJUMP;
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::JUMPATTACK_1;
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
		}

		if (NextState != eObjectState::END)
		{
			End();
			player->SetState(NextState);
		}
	}

	void Jump::End()
	{
		// ·£´õ
	}

}