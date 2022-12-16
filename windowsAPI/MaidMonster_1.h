#pragma once
#include "MonsterBase.h"

namespace sw
{
	class MaidMonster_1 : public MonsterBase
	{
	public:
		MaidMonster_1();
		~MaidMonster_1();

		virtual void InitializeAnimation() override;
		virtual void InitializeBox() override;
		virtual void InitalizeCollider() override;
	};
}