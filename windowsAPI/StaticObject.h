#pragma once
#include "GameObject.h"

namespace sw
{
	class StaticObject : public GameObject
	{
	public:
		StaticObject(std::wstring name);
		~StaticObject();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

	private:
	};
}

