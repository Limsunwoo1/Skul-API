#include "Attack.h"
#include "Move.h"
#include "StateHandle.h"
#include "Animator.h"
#include "Animation.h"
#include "Time.h"
#include "Input.h"
#include "AttackCollider.h"
#include "Rigidbody.h"

namespace sw
{
	Attack::Attack()
		: State()
		, mDelta(0.0f)
		, mAttackCount(0)
		, bInput(false)
	{
		/*mR_AttackSequence.push_back(L"R_AttackA");
		mR_AttackSequence.push_back(L"R_AttackB");

		mL_AttackSequence.push_back(L"L_AttackA");
		mL_AttackSequence.push_back(L"L_AttackB");*/
	}

	Attack::~Attack()
	{

	}

	void Attack::Start(Player* target)
	{
		SetTarget(target);
		StartCollider();
		SetStartAnimation();
	}
	void Attack::Run()
	{
		mDelta += Time::GetInstance()->DeltaTime();

		SetAnimation();
	}

	void Attack::End()
	{
		if(mCurCollider)
			mCurCollider->SetAble(true);

		mCurCollider = nullptr;
	}

	void Attack::StartCollider()
	{
		Player* player = GetTarget();
		eObjectState state = player->GetStateHandle()->
			GetState<Move>(eObjectState::LEFT)->GetDirtion();
		mCurCollider = nullptr;

		if (state == eObjectState::LEFT)
			mCurCollider = player->FindAttackCollider(mL_AttackSequence[mAttackCount]);
		else if (state == eObjectState::RIGHT)
			mCurCollider = player->FindAttackCollider(mR_AttackSequence[mAttackCount]);

		if(mCurCollider)
			mCurCollider->SetAble(false);
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

		mDelta = 0.0f;
	}

	void Attack::SetAnimation()
	{
		Player* player = GetTarget();
		Animator* animator = player->GetComponent<Animator>();
		if (mDelta < 0.4f)
		{
			// 이동하면서 공격 추가
			Player* player = GetTarget();
			StateHandle* statehandle = player->GetStateHandle();
			eObjectState state = player->GetStateHandle()->
				GetState<Move>(eObjectState::LEFT)->GetDirtion();

			if (KEY_PRESSE(eKeyCode::LEFT) && state == eObjectState::LEFT)
			{
				statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::LEFT);
				player->GetComponent<Rigidbody>()->AddForce(Vector2(-50.f, 0.0f));
			}
			else if (KEY_PRESSE(eKeyCode::RIGHT) && state == eObjectState::RIGHT)
			{
				statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::RIGHT);
				player->GetComponent<Rigidbody>()->AddForce(Vector2(50.f, 0.0f));
			}
			
			if (KEY_DOWN(eKeyCode::X))
				bInput = true;
			return;
		}

		if (animator->isComplete())
		{
			End();
			mDelta = 0.0f;
			player->SetState(eObjectState::IDLE);
			return;
		}

		if (bInput)
		{
			++mAttackCount;
			bInput = false;

			if (mAttackCount > player->GetMaxAttackCount())
				return;

			mDelta = 0.0f;
			End();
			Start(GetTarget());
		}
		

		/*End();
		mDelta = 0.0f;
		GetTarget()->SetState(eObjectState::IDLE);*/
	}
}