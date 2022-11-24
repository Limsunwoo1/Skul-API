#include "Move.h"
#include "Rigidbody.h"
#include "GameObject.h"
#include "Animator.h"

#include "Input.h"
#include "Jump.h"
#include "StateHandle.h"

namespace sw
{
	Move::Move()
	{
		
	}

	Move::~Move()
	{
		
	}

	void Move::Start(Player* target)
	{
		SetTarget(target);
	}

	void Move::Run()
	{
		Player* player = GetTarget();
		if (player == nullptr)
			return;

		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		eObjectState NextState = eObjectState::END;
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(500.f, 0.0f));
			mDirtion = eObjectState::RIGHT;
		}

		if (KEY_UP(eKeyCode::RIGHT))
		{
			NextState = eObjectState::IDLE;
		}

		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-500.f, 0.0f));
			mDirtion = eObjectState::LEFT;
		}

		if (KEY_UP(eKeyCode::LEFT))
		{
			NextState = eObjectState::IDLE;
		}

		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		if (jump->GetJumpCount() < 2)
		{
			if (KEY_PRESSE(eKeyCode::C))
			{
				NextState = eObjectState::JUMP;
			}
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
			player->SetState(NextState);
		}
	}

	void Move::End()
	{
		
	}

	void Move::SetDirtion(eObjectState type)
	{
		if (type == eObjectState::LEFT ||
			type == eObjectState::RIGHT)
			mDirtion = type;
	}

}