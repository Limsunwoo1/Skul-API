#include "Switch.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"

namespace sw
{
	Switch::Switch()
		: mSwitch(false)
	{
		
	}

	Switch::~Switch()
	{

	}

	void Switch::Start(PlayerBase* target)
	{
		SetTarget(target);

		// 방향설정
		PlayerBase* player = GetTarget();
		eObjectState state = player->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (state == eObjectState::LEFT)
			animator->Play(GetL_Animation(), false);
		else if (state == eObjectState::RIGHT)
			animator->Play(GetR_Animation(), false);
	}

	void Switch::Run()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		GetTarget()->SwitchSkill();

		if (animator->isComplete())
			GetTarget()->SetState(eObjectState::IDLE);
	}

	void Switch::End()
	{
		mSwitch = false;
	}
}
