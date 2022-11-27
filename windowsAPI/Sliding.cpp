#include "Sliding.h"
#include "Rigidbody.h"
#include "Input.h"
#include "StateHandle.h"
#include"Move.h"
#include "Time.h"
#include "Jump.h"
#include "Animator.h"

namespace sw
{
	Sliding::Sliding()
		: mDelta(0.0f)
		, mRuntime(0.2f)
		, mForce(2000.f)
		, mDelay(0.1f)
		, bSliding(false)
		, bInput(false)
		, mDirtion(eObjectState::END)
		, mInputState(eObjectState::END)
		, mSlidingCount(0)
	{

	}

	Sliding::~Sliding()
	{

	}

	void Sliding::Start(Player* target)
	{
		SetTarget(target);
		++mSlidingCount;
		mInputState = eObjectState::END;
		mDelta = 0.0f;

		if(mSlidingCount <= 2)
			target->SetIsShadow(true);

		SetStartAnimation();
	}

	void Sliding::Run()
	{
		if (GetTarget() == nullptr)
			return;

		mDelta += Time::GetInstance()->DeltaTime();

		if (SlidingRun())
			return;

		if (DoubleSlide())
			return;

		InputNextState();
	}

	void Sliding::End()
	{
		
	}

	void Sliding::SetStartAnimation()
	{
		mDirtion =
			GetTarget()->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();

		bSliding = true;

		Animator* animator = GetTarget()->GetComponent<Animator>();
		if (mDirtion == eObjectState::LEFT)
			animator->Play(L"L_Dash", true);
		else if (mDirtion == eObjectState::RIGHT)
			animator->Play(L"R_Dash", true);
	}

	bool Sliding::SlidingRun()
	{
		if (!bSliding)
			return false;

		if (mSlidingCount > 2)
		{
			mDelta = mDelay;
			bSliding = false;

			return false;
		}

		if (mDelta >= mRuntime)
		{
			bSliding = false;
			mDelta = 0.0f;

			return false;
		}

		float run = (mRuntime / mDelta);
		float Inforce = mForce / run;

		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* statehandle = GetTarget()->GetStateHandle();
		Move* move = statehandle->GetState<Move>(eObjectState::LEFT);

		if (mDirtion == eObjectState::RIGHT)
		{
			rigidbody->AddForce(Vector2(Inforce, 0.0f));
		}
		else if (mDirtion == eObjectState::LEFT)
		{
			rigidbody->AddForce(Vector2(-Inforce, 0.0f));
		}

		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			move->SetDirtion(eObjectState::RIGHT);
		}
		else if (KEY_PRESSE(eKeyCode::LEFT))
		{
			move->SetDirtion(eObjectState::LEFT);
		}

		return true;
	}

	bool Sliding::DoubleSlide()
	{
		// 딜레이 시간동안 재입력시 재시전
		if (mDelta > mDelay)
			return false;
		
		StateHandle* statehandle = GetTarget()->GetStateHandle();

		// objectState Left or Right 아무거나 입력
		Move* move = statehandle->GetState<Move>(eObjectState::LEFT);

		if (mSlidingCount <= 2)
		{
			if (KEY_PRESSE(eKeyCode::LEFT) && KEY_DOWN(eKeyCode::Z))
			{
				move->SetDirtion(eObjectState::LEFT);
				bInput = true;
			}
			else if (KEY_PRESSE(eKeyCode::RIGHT) && KEY_DOWN(eKeyCode::Z))
			{
				move->SetDirtion(eObjectState::RIGHT);
				bInput = true;
			}
			else if (KEY_DOWN(eKeyCode::Z))
			{
				bInput = true;
			}
		}
	}

	void Sliding::InputNextState()
	{
		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		Player* player = GetTarget();
		eObjectState NextState = eObjectState::END;
		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		// 재시전 입력되었는지
		if (bInput)
		{
			End();
			bInput = false;
			Start(GetTarget());
			return;
		}


		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				player->SetState(eObjectState::JUMP);
				return;
			}
		}

		if (rigidbody->GetGround())
		{
			NextState = eObjectState::IDLE;
		}
		else
		{
			NextState = eObjectState::DROP;
		}

		if (NextState != eObjectState::END)
		{
			End();
			player->SetState(NextState);
		}
	}
}