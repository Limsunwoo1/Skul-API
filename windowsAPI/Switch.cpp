#include "Switch.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"
#include "ObjectProjecTile.h"

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
		ObjectProjecTile* projectile = player->GetProjecTile(eSkilType::Switch);
		if (projectile != nullptr)
		{
			projectile->SetDeath(false);
			std::wstring name = projectile->GetEffectName();
			if (name != L"")
				projectile->GetComponent<Animator>()->Play(name);
		}

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
		if (player->GetProjecTile(eSkilType::Switch) != nullptr)
			player->GetProjecTile(eSkilType::Switch)->SetDeath(true);
		mSwitch = false;
	}
}
