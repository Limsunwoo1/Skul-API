#pragma once
#include "PlayerBase.h"

namespace sw
{
	class SwordSkul : public PlayerBase
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
		virtual void InitAttackCollider() override;
		virtual void InitSkils() override;

		virtual void OnAttackEffect(GameObject* other) override;

		virtual void SwitchProjecTile(GameObject* object) override;

		virtual void OnSkilB() override;

	private:
		Vector2 mArrivalPos;
	};
}


