#pragma once
#include "GameObject.h"

namespace sw
{
	class Missile : public GameObject
	{
	public:
		Missile();
		virtual ~Missile();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

	private:
		float mSpeed;
	};
}

