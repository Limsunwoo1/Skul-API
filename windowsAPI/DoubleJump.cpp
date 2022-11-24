#include "DouBleJump.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Animator.h"
#include "Input.h"
#include "StateHandle.h"
#include "Move.h"

namespace sw
{
	DoubleJump::DoubleJump()
	{
		
	}

	DoubleJump::~DoubleJump()
	{
		
	}

	void DoubleJump::Start(Player* target)
	{
		SetTarget(target);
		Rigidbody* rigidbody = target->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = -700.f;
		rigidbody->SetVelocity(velocity);
		rigidbody->SetGround(false);
	}

	void DoubleJump::Run()
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

		StateHandle* stathandle = player->GetStateHandle();
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

		if (KEY_DOWN(eKeyCode::Z))
		{
			player->SetState(eObjectState::SLIDING);
		}

		/*if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::JUMPATTACK_1;
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
		}*/
	}

	void DoubleJump::End()
	{
		
	}

}