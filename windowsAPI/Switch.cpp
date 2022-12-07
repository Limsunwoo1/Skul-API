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

		// ���⼳��
		PlayerBase* player = GetTarget();
		bool state = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!state)
			animator->Play(GetL_Animation(), false);
		else if (state)
			animator->Play(GetR_Animation(), false);
	}

	void Switch::Run()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		GetTarget()->SwitchSkill();

		if (animator->isComplete())
			GetTarget()->SetState(ePlayerState::IDLE);
	}

	void Switch::End()
	{
		mSwitch = false;
	}
}
