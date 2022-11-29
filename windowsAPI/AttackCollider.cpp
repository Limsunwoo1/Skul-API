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
		if (!isAble)
			return;

		mCollider->Render(hdc);
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