#pragma once
#include "GameObject.h"

namespace sw
{
	class Collider;
	class AttackCollider : public GameObject
	{
	public:
		AttackCollider(GameObject* owner);
		~AttackCollider();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetOffset() { return mOffset; }

		void SetName(std::wstring name) { mName = name;}
		std::wstring GetName() { return mName; }

		bool GetAble() { return IsDeath(); }
		void SetAble(bool anable);

	private:
		std::wstring mName;
		GameObject* mOwner;
		Collider* mCollider;

		Vector2 mOffset;
	};
}

