#pragma once
#include "Scene.h"

namespace sw
{
	class PlayScene2 : public Scene
	{
	public:
		PlayScene2();
		virtual ~PlayScene2();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	private:


	};
}
