#pragma once
#include "MonsterBase.h"

namespace sw
{
	class SwordMonster : public MonsterBase
	{
	public:
		SwordMonster();
		~SwordMonster();

		virtual void InitializeAnimation() override;
		virtual void InitializeBox() override;
		virtual void InitalizeCollider() override;
	};
}