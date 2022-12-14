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

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void InitAnimtion() override;
		virtual void InitState() override;
		virtual void InitAttackCollider() override;

		virtual void SwitchSkill() override;
		virtual void DashEffect() override;
		virtual void OnAttackEffect(GameObject* other) override;

	};
}

