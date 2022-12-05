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
		, mInputState(eObjectState::END)
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
			GetTarget()->GetStateHandle()->GetState<Move>(eObjectState::MOVE)->GetDirtion();

		bSliding = true;

		Animator* animator = GetTarget()->GetComponent<Animator>();
		if (!mDirtion)
			animator->Play(GetL_Animation(), true);
		else if (mDirtion)
			animator->Play(GetR_Animation(), true);
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
		Move* move = statehandle->GetState<Move>(eObjectState::MOVE);

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
		// ������ �ð����� ���Է½� �����
		if (mDelta > mDelay)
			return false;
		
		StateHandle* statehandle = GetTarget()->GetStateHandle();

		// objectState Left or Right �ƹ��ų� �Է�
		Move* move = statehandle->GetState<Move>(eObjectState::MOVE);

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
			else if (KEY_DOWN(eKeyCode::Z))
			{
				bInput = true;
			}
		}
	}

	void Sliding::InputNextState()
	{
		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		PlayerBase* player = GetTarget();
		eObjectState NextState = eObjectState::END;
		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		// ����� �ԷµǾ�����
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