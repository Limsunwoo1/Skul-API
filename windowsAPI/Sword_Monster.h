#pragma once
#include "MonsterBase.h"

namespace sw
{
	class SwordMonster : public MonsterBase
	{
	public:
		SwordMonster();
		~SwordMonster();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		virtual void OnCollisionExit() override;

		virtual void IDLE() ;
		virtual void Attack() ;
		virtual void Move() ;
		virtual void Hit() ;
	};
}