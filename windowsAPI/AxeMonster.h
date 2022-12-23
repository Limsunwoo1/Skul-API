#pragma once
#include "MonsterBase.h"

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

		void OnSkilAttack();
		void SkilAttack(GameObject* other);
	private:
		std::vector<ObjectProjecTile*> mProjecTile;
	};
}