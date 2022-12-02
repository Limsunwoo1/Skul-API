#pragma once
#include "PlayerBase.h"

namespace sw
{
	class BasicSkul : public PlayerBase
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

		void R_AttackA();
		void R_AttackB();
		void R_AttackADelete();
		void R_AttackBDelete();

		void L_AttackA();
		void L_AttackB();
		void L_AttackADelete();
		void L_AttackBDelete();
	};
}

