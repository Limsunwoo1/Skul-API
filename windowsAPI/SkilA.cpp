#include "SkilA.h"
#include "ObjectProjecTile.h"
#include "Animator.h"
#include "Move.h"
#include "PlayerBase.h"
#include "StateHandle.h"
#include "samurai.h"
#include "EventManager.h"
namespace sw
{
	SkilA::SkilA()
	{

	}

	SkilA::~SkilA()
	{

	}

	void SkilA::Start(PlayerBase* target)
	{
		SetTarget(target);

		Samurai* samurai = dynamic_cast<Samurai*>(target);
		if (samurai)
		{
			samurai->SkillAStart();
			return;
		}

		PlayerBase* player = GetTarget();
		bool dirc = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!dirc)
			animator->Play(GetL_Animation(), false);
		else if (dirc)
			animator->Play(GetR_Animation(), false);

		// 방향설정
		ObjectProjecTile* projectile = player->GetProjecTile(eSkilType::SkilA);
		if (projectile != nullptr)
		{
			projectile->SetDeath(false);
			Vector2 offset = projectile->GetOffset();
			std::wstring name = projectile->GetEffectName();
			if (name == L"")
				return;

			if (dirc)
			{
				name = L"R" + name;
				offset.x = fabs(offset.x);
				offset.y = fabs(offset.y);
			}
			else
			{
				name = L"L" + name;
				offset.x = -1 * (fabs(offset.x));
				offset.y = -1 * (fabs(offset.y));
			}
			projectile->SetOffset(offset);
			projectile->GetComponent<Animator>()->Play(name);
		}
	}

	void SkilA::Run()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		Samurai* samurai = dynamic_cast<Samurai*>(GetTarget());
		if (samurai)
			return;

		GetTarget()->OnSkilA();

		if (animator->isComplete())
		{
			End();
			GetTarget()->SetState(ePlayerState::IDLE);
		}
	}

	void SkilA::End()
	{
		PlayerBase* player = GetTarget();
		if (player->GetProjecTile(eSkilType::SkilA) != nullptr)
			player->GetProjecTile(eSkilType::SkilA)->SetDeath(true);
	}
}