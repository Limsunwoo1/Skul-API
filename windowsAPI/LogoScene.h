#pragma once
#include "Scene.h"

namespace sw
{
	class LogoScene : public Scene
	{
	public:
		LogoScene();
		virtual ~LogoScene();

		void Initialize() override;
		void Tick() override;
		void Render(HDC hdc) override;

	private:


	};
}
