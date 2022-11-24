#include "Component.h"

namespace sw
{
	Component::Component(eComponentType type)
		: mType(type)
		, mOwner(nullptr)
	{
	}

	Component::~Component()
	{
	}

	void Component::Render(HDC hdc)
	{
	}
}
