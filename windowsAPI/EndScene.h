#pragma once
#include "Scene.h"

namespace sw
{
	class EndScene : public Scene
	{
	public:
		EndScene();
		virtual ~EndScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();
	private:


	};
}
