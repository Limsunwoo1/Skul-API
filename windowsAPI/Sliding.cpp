#include "Sliding.h"
#include "Rigidbody.h"
#include "Input.h"
#include "StateHandle.h"
#include"Move.h"
#include "Time.h"
#include "Jump.h"

namespace sw
{
	Sliding::Sliding()
		: mDelta(0.0f)
		, mRuntime(0.2f)
		, mForce(3000.f)
		, mDelay(0.15f)
		, bSliding(false)
		, bInput(false)
		, mDirtion(eObjectState::END)
		, mInputState(eObjectState::END)
	{

	}

	Sliding::~Sliding()
	{

	}

	void Sliding::Start(Player* target)
	{
		SetTarget(target);
		mInputState = eObjectState::END;
		mDelta = 0.0f;

		mDirtion =
			target->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();

		

		bSliding = true;
	}

	void Sliding::Run()
	{
		Player* player = GetTarget();
		if (player == nullptr)
			return;

		mDelta += Time::GetInstance()->DeltaTime();

		if (bSliding)
		{
			float run = (mRuntime / mDelta);
			float Inforce = mForce / run;

			Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
				

			if (mDirtion == eObjectState::RIGHT)
			{
				rigidbody->AddForce(Vector2(Inforce, 0.0f));
			}
			else if (mDirtion == eObjectState::LEFT)
			{
				rigidbody->AddForce(Vector2(-Inforce, 0.0f));
			}

			if (mDelta >= mRuntime)
			{
				bSliding = false;
				mDelta = 0.0f;
			}

			return;
		}

		if (mDelta < mDelay)
			return;

		//player->GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 500.f));
		eObjectState NextState = eObjectState::END;
		Rigidbody* rigidbody = GetTarget()->GetComponent<Rigidbody>();
		StateHandle* stateHandle = GetTarget()->GetStateHandle();
		Jump* jump = stateHandle->GetState<Jump>(eObjectState::JUMP);

		if (jump->GetJumpCount() < 2)
		{
			if (KEY_PRESSE(eKeyCode::C))
			{
				player->SetState(eObjectState::JUMP);
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

	void Sliding::End()
	{
		
	}
}