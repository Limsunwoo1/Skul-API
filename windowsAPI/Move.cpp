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
		// true = ¿À¸¥ÂÊ false = ¿ÞÂÊ
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
			player->GetComponent<Rigidbody>()->AddForce(Vector2(400.f, 0.0f));
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
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-400.f, 0.0f));
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
		eObjectState nextState = eObjectState::END;
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				nextState = eObjectState::JUMP;
			}
		}
		else if (KEY_DOWN(eKeyCode::X))
		{
			nextState = eObjectState::ATTACK;
		}
		else if (KEY_DOWN(eKeyCode::Z) ||
			KEY_PRESSE(eKeyCode::LEFT) && KEY_DOWN(eKeyCode::Z) ||
			KEY_PRESSE(eKeyCode::RIGHT) && KEY_DOWN(eKeyCode::Z))
		{
			nextState = eObjectState::SLIDING;
		}
		else if (KEY_UP(eKeyCode::RIGHT))
		{
			nextState = eObjectState::IDLE;
		}
		else if (KEY_UP(eKeyCode::LEFT))
		{
			nextState = eObjectState::IDLE;
		}

		if (nextState != eObjectState::END)
		{
			End();
			GetTarget()->SetState(nextState);
		}
	}

}