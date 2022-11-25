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
		mCurAnimation = L"";
	}

	void Move::Run()
	{
		Player* player = GetTarget();
		if (player == nullptr)
			return;

		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		Animator* animator = GetTarget()->GetComponent<Animator>();
		eObjectState NextState = eObjectState::END;
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(500.f, 0.0f));
			mDirtion = eObjectState::RIGHT;

			if (mCurAnimation != L"R_RUN")
			{
				animator->Play(L"R_RUN", true);
				mCurAnimation = L"R_RUN";
			}
		}
		else if (KEY_PRESSE(eKeyCode::LEFT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-500.f, 0.0f));
			mDirtion = eObjectState::LEFT;

			if (mCurAnimation != L"L_RUN")
			{
				animator->Play(L"L_RUN", true);
				mCurAnimation = L"L_RUN";
			}
		}

		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				NextState = eObjectState::JUMP;
			}
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			NextState = eObjectState::ATTACK_1;
		}
		else if (KEY_DOWN(eKeyCode::Z) || 
			KEY_PRESSE(eKeyCode::LEFT) && KEY_DOWN(eKeyCode::Z) || 
			KEY_PRESSE(eKeyCode::RIGHT) && KEY_DOWN(eKeyCode::Z))
		{
			NextState = eObjectState::SLIDING;
		}
		else if (KEY_UP(eKeyCode::RIGHT))
		{
			NextState = eObjectState::IDLE;
		}
		else if (KEY_UP(eKeyCode::LEFT))
		{
			NextState = eObjectState::IDLE;
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