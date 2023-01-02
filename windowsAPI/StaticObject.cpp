#include "StaticObject.h"
#include "Animator.h"
namespace sw
{
	StaticObject::StaticObject(std::wstring name)
	{
		Initialize();
		GetComponent<Animator>()->Play(name);
	}

	StaticObject::~StaticObject()
	{
	}

	void StaticObject::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);

		animator->CreatAnimations(L"StaticObject1", L"..\\Resource\\Animation\\StaticObject\\Object01");
		animator->CreatAnimations(L"StaticObject2", L"..\\Resource\\Animation\\StaticObject\\Object02");
		animator->CreatAnimations(L"StaticObject3", L"..\\Resource\\Animation\\StaticObject\\Object03");
		animator->CreatAnimations(L"StaticObject4", L"..\\Resource\\Animation\\StaticObject\\Object04");
		animator->CreatAnimations(L"StaticObject5", L"..\\Resource\\Animation\\StaticObject\\Object05");
		animator->CreatAnimations(L"StaticObject6", L"..\\Resource\\Animation\\StaticObject\\Object06");
		animator->CreatAnimations(L"StaticObject7", L"..\\Resource\\Animation\\StaticObject\\Object07");
		animator->CreatAnimations(L"StaticObject8", L"..\\Resource\\Animation\\StaticObject\\Object08");
		animator->CreatAnimations(L"StaticObject9", L"..\\Resource\\Animation\\StaticObject\\Object09");
		animator->CreatAnimations(L"StaticObject10", L"..\\Resource\\Animation\\StaticObject\\Object10");
		animator->CreatAnimations(L"StaticObject11", L"..\\Resource\\Animation\\StaticObject\\Object11");
		animator->CreatAnimations(L"StaticObject12", L"..\\Resource\\Animation\\StaticObject\\Object12");
		animator->CreatAnimations(L"StaticObject13", L"..\\Resource\\Animation\\StaticObject\\Object13");
		animator->CreatAnimations(L"StaticObject14", L"..\\Resource\\Animation\\StaticObject\\Object14");
		animator->CreatAnimations(L"StaticObject15", L"..\\Resource\\Animation\\StaticObject\\Object15");
	}

	void StaticObject::Tick()
	{
		GameObject::Tick();
	}

	void StaticObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}