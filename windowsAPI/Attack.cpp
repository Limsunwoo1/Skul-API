#include "Attack.h"
#include "Move.h"
#include "StateHandle.h"
#include "Animator.h"
#include "Animation.h"
#include "Time.h"
#include "Input.h"

namespace sw
{
	Attack::Attack()
		: State()
		, mDelta(0.0f)
		, mAttackCount(0)
		, bInput(false)
	{
		mR_AttackSequence.push_back(L"R_AttackA");
		mR_AttackSequence.push_back(L"R_AttackB");

		mL_AttackSequence.push_back(L"L_AttackA");
		mL_AttackSequence.push_back(L"L_AttackB");
	}

	Attack::~Attack()
	{

	}

	void Attack::Start(Player* target)
	{
		SetTarget(target);
		SetStartAnimation();
	}
	void Attack::Run()
	{
		//mDelta += Time::GetInstance()->DeltaTime();

		SetAnimation();
	}

	void Attack::End()
	{

	}

	void Attack::SetStartAnimation()
	{
		// 방향설정
		Player* player = GetTarget();
		eObjectState state = player->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (state == eObjectState::LEFT)
			animator->Play(mL_AttackSequence[mAttackCount], false);
		else if (state == eObjectState::RIGHT)
			animator->Play(mR_AttackSequence[mAttackCount], false);
	}

	void Attack::SetAnimation()
	{
		Player* player = GetTarget();
		Animator* animator = player->GetComponent<Animator>();
		if (animator->isComplete())
		{
			End();
			mDelta = 0.0f;
			GetTarget()->SetState(eObjectState::IDLE);
			return;
		}

		if (KEY_DOWN(eKeyCode::X))
		{
			++mAttackCount;
			mDelta = 0.0f;

			if (mAttackCount > GetTarget()->GetMaxAttackCount())
				return;

			End();
			Start(GetTarget());
		}
		

		/*End();
		mDelta = 0.0f;
		GetTarget()->SetState(eObjectState::IDLE);*/
	}
}