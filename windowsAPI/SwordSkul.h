#pragma once
#include "Player.h"

namespace sw
{
	class SwordSkul : public Player
	{
	public:
		SwordSkul();
		virtual ~SwordSkul();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void InitAnimtion() override;
		virtual void InitState() override;
	};
}


