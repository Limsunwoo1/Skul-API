#pragma once
#include "GameObject.h"

namespace sw
{
	class Meteor : public GameObject
	{
	public:
		Meteor();
		virtual ~Meteor();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		Vector2D speed;
	};
}

