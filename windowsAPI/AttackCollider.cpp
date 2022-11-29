#include "AttackCollider.h"
#include "Collider.h"
#include "Camera.h"
#include "Player.h"

namespace sw
{
	AttackCollider::AttackCollider(GameObject* owner)
	{
		mOwner = owner;
		Player* player = dynamic_cast<Player*>(owner);

		if(player != nullptr)
			player->PushAttackCollider(this);

		Collider* collider = AddComponent<Collider>();
		mCollider = collider;
		collider->SetOwner(this);

		bool death = true;
		SetAble(death);
	}

	AttackCollider::~AttackCollider()
	{
	}

	void AttackCollider::Tick()
	{
		if (mOwner == nullptr)
			return;
		if (mCollider == nullptr)
			return;
		if (IsDeath())
			return;

		GameObject::Tick();

		Vector2 ownerPos = mOwner->GetPos();
		ownerPos = ownerPos + mOffset;

		mCollider->SetPos(ownerPos);
		mCollider->SetScale(GetScale());
		mCollider->SetOffset(GetOffset());
	}

	void AttackCollider::Render(HDC hdc)
	{
		if (mCollider == nullptr)
			return;
		if (IsDeath())
			return;

		mCollider->Render(hdc);
	}

	void AttackCollider::SetAble(bool anable)
	{
		if (mCollider == nullptr)
			return;

		SetDeath(anable);
	}

	void AttackCollider::OnCollisionEnter(Collider* other)
	{
	}

	void AttackCollider::OnCollisionStay(Collider* other)
	{
	}

	void AttackCollider::OnCollisionExit(Collider* other)
	{
	}
}