#include "Switch.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Move.h"
#include "StateHandle.h"
#include "ObjectProjecTile.h"
#include "samurai.h"
#include "SwordSkul.h"
namespace sw
{
	Switch::Switch()
		: mSwitch(false)
		, mSkul(eSkulHead::Basic)
	{
		
	}

	Switch::~Switch()
	{

	}

	void Switch::Start(PlayerBase* target)
	{
		SetTarget(target);
		SwitchSound();
		Samurai* samurai = dynamic_cast<Samurai*>(target);
		if (samurai)
		{
			samurai->SwitchStart();
			return;
		}
		// 방향설정
		PlayerBase* player = GetTarget();
		ObjectProjecTile* projectile = player->GetProjecTile(eSkilType::Switch);
		if (projectile != nullptr)
		{
			projectile->SetDeath(false);
			std::wstring name = projectile->GetEffectName();
			SwordSkul* sword = dynamic_cast<SwordSkul*>(target);
			if (sword)
			{
				if (name != L"")
					projectile->GetComponent<Animator>()->Play(name,true);
			}
			else if (name != L"")
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
		Samurai* samurai = dynamic_cast<Samurai*>(GetTarget());
		if (samurai)
			return;

		GetTarget()->SwitchSkill();

		if (animator->isComplete())
		{
			End();
			GetTarget()->SetState(ePlayerState::IDLE);
		}
	}

	void Switch::End()
	{
		if (mSkul == eSkulHead::Sword)
			sw::SwordSkulSwitch.Stop(true);

		PlayerBase* player = GetTarget();
		if (player->GetProjecTile(eSkilType::Switch) != nullptr)
			player->GetProjecTile(eSkilType::Switch)->SetDeath(true);
		mSwitch = false;
	}
	void Switch::SwitchSound()
	{
		switch (mSkul)
		{
		case eSkulHead::Basic:
		{
			
		}
		break;
		case eSkulHead::Sword:
		{
			sw::SwordSkulSwitch.Play(false);
		}
		break;
		case eSkulHead::Samurai:
		{

		}
		break;
		}
	}
}
