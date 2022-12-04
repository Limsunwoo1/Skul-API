#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class Wood_Monster_1 : public GameObject
	{
	public:
		Wood_Monster_1();
		~Wood_Monster_1();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		virtual void OnCollisionEnter() override;
		virtual void OnCollisionStay() override;
		virtual void OnCollisionExit() override;

	private:
		Image* mImage;
		int alpha;
	};
}