#pragma once
#include "GameObject.h"

namespace sw
{
	class Ground : public GameObject
	{
	public:
		Ground();
		~Ground();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void CheckCollider(Collider* other);
		void Top_Bottom_Collider(Collider* other);
		void SetAngle();

		eColliderLayer GetLayer() { return type; }
	private:
		float mAngle;

		eColliderLayer type;
	};
}

