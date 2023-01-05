#include "SkilB.h"
#include "ObjectProjecTile.h"
#include "Animator.h"
#include "Move.h"
#include "PlayerBase.h"
#include "StateHandle.h"
#include "samurai.h"
#include "EventManager.h"
namespace sw
{
	SkilB::SkilB()
		: mSkul(eSkulHead::Basic)
	{

	}

	SkilB::~SkilB()
	{

	}

	void SkilB::Start(PlayerBase* target)
	{
		SetTarget(target);
		SkillBSound();
		PlayerBase* player = GetTarget();
		bool dirc = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!dirc)
			animator->Play(GetL_Animation(), false);
		else if (dirc)
			animator->Play(GetR_Animation(), false);

		// 방향설정
		ObjectProjecTile* projectile = player->GetProjecTile(eSkilType::SkilB);
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

			if (projectile->GetNotMove())
				projectile->SetPos(GetTarget()->GetPos() + projectile->GetOffset());

		}
	}

	void SkilB::Run()
	{
		Animator* animator = GetTarget()->GetComponent<Animator>();
		GetTarget()->OnSkilB();


		if (animator->isComplete())
		{
			End();
			GetTarget()->SetState(ePlayerState::IDLE);
		}
	}

	void SkilB::End()
	{
		PlayerBase* player = GetTarget();
		if (player->GetProjecTile(eSkilType::SkilB) != nullptr)
			player->GetProjecTile(eSkilType::SkilB)->SetDeath(true);
	}
	void SkilB::SkillBSound()
	{
		switch (mSkul)
		{
		case eSkulHead::Basic:
		{
			
		}
		break;
		case eSkulHead::Sword:
		{
			sw::SwordSkulSKillB.Play(false);
		}
		break;
		case eSkulHead::Samurai:
		{
			sw::SamuraiSkulSKillB.Play(false);
		}
		break;
		}
	}
}