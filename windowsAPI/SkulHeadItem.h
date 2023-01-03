#pragma once
#include "GameObject.h"

namespace sw
{

	class SkulHeadItem : public GameObject
	{
	public:
		SkulHeadItem();
		~SkulHeadItem();

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetSkulHeadType(eSkulHead type) { mHeadType = type; }
	private:
		eSkulHead mHeadType;
	};
}

