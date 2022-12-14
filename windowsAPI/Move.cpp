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
		// true = ?????? false = ????
		mDirction = true;
	}

	Move::~Move()
	{
		
	}

	void Move::Start(PlayerBase* target)
	{
		SetTarget(target);
		mCurAnimation = L"";
	}

	void Move::Run()
	{
		if (GetTarget() == nullptr)
			return;
	
		SetAnimation();
		NextState();
	}

	void Move::End()
	{
		
	}

	void Move::SetDirtion(bool dirction)
	{
		mDirction = dirction;
	}

	void Move::SetAnimation()
	{
		PlayerBase* player = GetTarget();
		Animator* animator = GetTarget()->GetComponent<Animator>();
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(400, 0.0f));
			mDirction = true;
			std::wstring setAnimation = GetR_Animation();
			if (mCurAnimation != setAnimation)
			{
				animator->Play(setAnimation, true);
				mCurAnimation = setAnimation;
			}
		}
		else if (KEY_PRESSE(eKeyCode::LEFT))
		{
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-400, 0.0f));
			mDirction = false;
			std::wstring setAnimation = GetL_Animation();
			if (mCurAnimation != setAnimation)
			{
				animator->Play(setAnimation, true);
				mCurAnimation = setAnimation;
			}
		}
	}

	void Move::NextState()
	{
		ePlayerState nextState = ePlayerState::END;
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(ePlayerState::JUMP);

		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				nextState = ePlayerState::JUMP;
			}
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			nextState = ePlayerState::ATTACK;
		}
		else if (KEY_DOWN(eKeyCode::A))
		{
			nextState = ePlayerState::SKILL_A;
		}
		else if (KEY_DOWN(eKeyCode::S))
		{
			nextState = ePlayerState::SKILL_B;
		}
		else if (KEY_PRESSE(eKeyCode::LEFT) && KEY_DOWN(eKeyCode::Z)
			 ||  KEY_PRESSE(eKeyCode::RIGHT) && KEY_DOWN(eKeyCode::Z))
		{
			nextState = ePlayerState::SLIDING;
		}
		else if (KEY_UP(eKeyCode::RIGHT))
		{
			nextState = ePlayerState::IDLE;
		}
		else if (KEY_UP(eKeyCode::LEFT))
		{
			nextState = ePlayerState::IDLE;
		}

		if (nextState != ePlayerState::END)
		{
			End();
			GetTarget()->SetState(nextState);
		}
	}

}