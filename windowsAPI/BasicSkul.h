#pragma once
#include "Player.h"

namespace sw
{
	class AttackCollider;
	class BasicSkul : public Player
	{
	public:
		BasicSkul();
		virtual ~BasicSkul();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void InitAnimtion() override;
		virtual void InitState() override;

	};
}

