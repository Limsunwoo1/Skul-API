#include "Ground.h"
#include "Player.h"
#include "Collider.h"
#include "Rigidbody.h"


namespace sw
{
	Ground::Ground()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(1000.f, 50.f));
	}
	Ground::~Ground()
	{
	}
	void Ground::Tick()
	{
		GameObject::Tick();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		playerObj->GetComponent<Rigidbody>()->SetGround(true);

		Vector2 pPos = other->GetPos();
		Vector2 pSca = other->GetScale();

		Vector2 mCPos = GetComponent<Collider>()->GetPos();
		Vector2 mCScale = GetComponent<Collider>()->GetScale();
		
		float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fScale = (other->GetScale().y / 2.0f) + (GetComponent<Collider>()->GetScale().y / 2.0f);

		if (fLen < fScale)
		{
			Vector2 playerPos = playerObj->GetPos();
			playerPos.y -= (fScale - fLen) - 1.0f;
			playerObj->SetPos(playerPos);
		}
	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
	}
}
