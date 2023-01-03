#pragma once
#include "HUD.h"

namespace sw
{
	class GameObject;
	class HpBar : public HUD
	{
	public:
		HpBar(eUIType type);
		~HpBar();

		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;

		void SetTarget(GameObject* target) { mTarget = target; }
		GameObject* GetTarget() { return mTarget; }
	private:
		GameObject* mTarget;
	};
}

