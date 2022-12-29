#pragma once
#include "BossMonster.h"


namespace sw
{
	class Scene;
	class LeianaControler;
	class LeianaBossRight : public BossMonster
	{
	public:
		LeianaBossRight();
		~LeianaBossRight();

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

		virtual void Patton1_Stand_by( bool type = true) override;
		virtual void Patton1_Progress() override;
		virtual void Patton2_Stand_by( bool type = true) override;
		virtual void Patton2_Progress() override;
		virtual void Patton3_Stand_by( bool type = true) override;
		virtual void Patton3_Progress() override;
		virtual void Patton4_Stand_by( bool type = true) override;
		virtual void Patton4_Progress() override;

		void SetOwer(LeianaControler* owner) { mOwner = owner; }
		LeianaControler* GetOwner() { return mOwner; }

	private:
		LeianaControler* mOwner;
	};
}

