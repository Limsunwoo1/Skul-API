#pragma once
#include "Scene.h"

namespace sw
{
	class StartScene : public Scene
	{
	public:
		StartScene();
		~StartScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();

	private:

	};
}

