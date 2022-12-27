#pragma once
#include "BossMonster.h"


namespace sw
{
	class LeianaBoss : public BossMonster
	{
	public:
		LeianaBoss();
		~LeianaBoss();

		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void Initialize() override;
		virtual void InitializeAnimation() override;
		virtual void InitalizeCollider() override;
		virtual void InitalizeProjecTile() override;

		virtual void Idle() override;
		virtual void Patton1() override;
		virtual void Patton2() override;
		virtual void Patton3() override;
		virtual void Patton4() override;

	private:
		GameObject* mLeftBoss;
		GameObject* mRightBoss;
		GameObject* mDarkBoss;

		bool mDualMode;
		bool mSoloMode;
		bool mDarkMode;
	};
}

