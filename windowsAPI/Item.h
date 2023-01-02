#pragma once
#include "GameObject.h"

namespace sw
{
	class Item : public GameObject
	{
	public:
		Item();
		~Item();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize() override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetDeactiveate(bool active) { mbDeactivate = active; }
		bool GetDeactivate() { return mbDeactivate; }
	private:
		UINT mMonsterCount;
		bool mbDeactivate;
	};
}

