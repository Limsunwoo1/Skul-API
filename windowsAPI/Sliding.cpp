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
		, mDirtion(true)
		, mInputState(ePlayerState::END)
		, mSlidingCount(0)
	{

	}

	Sliding::~Sliding()
	{

	}

	void Sliding::Start(PlayerBase* target)
	{
		SetTarget(target);
		++mSlidingCount;
		mInputState = ePlayerState::END;
		mDelta = 0.0f;

		if (mSlidingCount <= 2)
		{
			sw::DashSound.Play(false);
			target->SetIsShadow(true);
		}

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
		bInput = false;
	}

	void Sliding::SetStartAnimation()
	{
		mDirtion =
			GetTarget()->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		GetTarget()->SetSildingDirction(mDirtion);
		
		bSliding = true;

		Animator* animator = GetTarget()->GetComponent<Animator>();
		if (!mDirtion)
			animator->Play(GetL_Animation(), false);
		else if (mDirtion)
			animator->Play(GetR_Animation(), false);
	}

	bool Sliding::SlidingRun()
	{
		if (!bSliding)
			return false;

		if (mSlidingCount > 2)
		{
			mDelta = mDelay;
			bSliding = false;

			return true;
		}

		if (mDelta >= mRuntime)
		{
			bSliding = false;
			mDelta = 0.0f;

			return true;
		}

		float run = (mRuntime / mDelta);
		float Inforce = mForce / run;

		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* statehandle = GetTarget()->GetStateHandle();
		Move* move = statehandle->GetState<Move>(ePlayerState::MOVE);

		if (mDirtion)
		{
			rigidbody->AddForce(Vector2(Inforce, 0.0f));
		}
		else if (!mDirtion)
		{
			rigidbody->AddForce(Vector2(-Inforce, 0.0f));
		}

		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			move->SetDirtion(true);
		}
		else if (KEY_PRESSE(eKeyCode::LEFT))
		{
			move->SetDirtion(false);
		}

		return true;
	}

	bool Sliding::DoubleSlide()
	{
		// 딜레이 시간동안 재입력시 재시전
		if (mDelta > mDelay)
			return false;
		
		StateHandle* statehandle = GetTarget()->GetStateHandle();
		Move* move = statehandle->GetState<Move>(ePlayerState::MOVE);

		if (mSlidingCount <= 2)
		{
			if (KEY_PRESSE(eKeyCode::LEFT) && KEY_DOWN(eKeyCode::Z))
			{
				move->SetDirtion(false);
				bInput = true;
			}
			else if (KEY_PRESSE(eKeyCode::RIGHT) && KEY_DOWN(eKeyCode::Z))
			{
				move->SetDirtion(true);
				bInput = true;
			}
		}

		return true;
	}

	void Sliding::InputNextState()
	{
		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		PlayerBase* player = GetTarget();
		ePlayerState NextState = ePlayerState::END;
		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(ePlayerState::JUMP);

		// 재시전 입력되었는지
		if (bInput)
		{
			End();
			Start(GetTarget());
			return;
		}


		if (KEY_PRESSE(eKeyCode::C))
		{
			if (jump->GetJumpCount() < 2)
			{
				End();
				player->SetState(ePlayerState::JUMP);
				return;
			}
		}

		if (rigidbody->GetGround())
		{
			NextState = ePlayerState::IDLE;
		}
		else
		{
			NextState = ePlayerState::DROP;
		}

		if (NextState != ePlayerState::END)
		{
			End();
			player->SetState(NextState);
		}
	}
}