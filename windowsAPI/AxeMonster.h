#pragma once
#include "MonsterBase.h"
#include "GenericAnimator.h"
namespace sw
{
	class ObjectProjecTile;
	class AxeMonster : public MonsterBase
	{
	public:
		AxeMonster();
		~AxeMonster();

		virtual void InitializeAnimation() override;
		virtual void InitializeBox() override;
		virtual void InitalizeCollider() override;

		virtual void Tick() override;

		virtual void Hit() override;
		virtual void ProejcTielDelte() override;

		void OnSkilAttack();
		void OnSkillSound();
		void SkilAttack(GameObject* other);
	private:
		std::vector<ObjectProjecTile*> mProjecTile;
		GenericAnimator MyGenericAnimator;
		float mAttackSound;
	};
}