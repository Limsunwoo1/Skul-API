#pragma once
#include "GateObject.h"

namespace sw
{
	class BossGate : public GateObject
	{
	public:
		BossGate();
		~BossGate();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize()override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
	};
}

