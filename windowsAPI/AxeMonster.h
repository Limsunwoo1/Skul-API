#pragma once
#include "MonsterBase.h"

namespace sw
{
	class AxeMonster : public MonsterBase
	{
	public:
		AxeMonster();
		~AxeMonster();

		virtual void InitializeAnimation() override;
		virtual void InitializeBox() override;
		virtual void InitalizeCollider() override;

		virtual void Hit() override;
	};
}