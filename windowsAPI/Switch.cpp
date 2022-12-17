#include "Switch.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"
#include "ObejctProjecTile.h"

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
		if(player->GetProjecTile() != nullptr)
			player->GetProjecTile()->SetDeath(false);

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
		{
			End();
			GetTarget()->SetState(ePlayerState::IDLE);
		}
	}

	void Switch::End()
	{
		PlayerBase* player = GetTarget();
		if (player->GetProjecTile() != nullptr)
			player->GetProjecTile()->SetDeath(true);
		mSwitch = false;
	}
}
