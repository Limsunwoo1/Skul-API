#pragma once
#include "Scene.h"

namespace sw
{
	class LeianaControler;
	class Ch2BossScene : public Scene
	{
	public:
		Ch2BossScene();
		~Ch2BossScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter() override;
		virtual void Exit() override;

		virtual void Release() override;
	private:
		LeianaControler* mBoss;
	};
}

