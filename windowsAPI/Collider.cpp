#include "Collider.h"
#include "GameObject.h"
#include "Application.h"
#include "Camera.h"
#include "Ground.h"

namespace sw
{
	Collider::Collider()
		: Component(eComponentType::Collider)
		, mOffset(Vector2::Zero)
		, mPos(Vector2::Zero)
		, mScale(Vector2::One)
		, mCollisionCount(0)
	{

	}

	Collider::~Collider()
	{

	}

	void Collider::Tick()
	{
		GameObject* owner = GetOwner();
		mPos = owner->GetPos() + mOffset;
		//mScale = owner->GetScale();
	}

	void Collider::Render(HDC hdc)
	{
		return;
		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);

		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN redPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		HPEN oldPen = NULL;

		if (mCollisionCount > 0)
			oldPen = (HPEN)SelectObject(hdc, redPen);
		else
			oldPen = (HPEN)SelectObject(hdc, greenPen);

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		Rectangle(hdc, pos.x - (mScale.x * 0.5), pos.y - (mScale.y * 0.5)
			, pos.x + (mScale.x * 0.5), pos.y + (mScale.y * 0.5));
		

		SelectObject(hdc, oldPen);
		DeleteObject(redPen);
		DeleteObject(greenPen);
	}

	void Collider::OnCollisionEnter(Collider* other)
	{
		mCollisionCount++;
		GetOwner()->OnCollisionEnter(other);
	}

	void Collider::OnCollisionStay(Collider* other)
	{
		GetOwner()->OnCollisionStay(other);
	}

	void Collider::OnCollisionExit(Collider* other)
	{
		mCollisionCount--;
		GetOwner()->OnCollisionExit(other);
	}

	void Collider::OnCollisionEnter()
	{
		mCollisionCount++;
		GetOwner()->OnCollisionEnter();
	}
	void Collider::OnCollisionStay()
	{
		GetOwner()->OnCollisionStay();
	}
	void Collider::OnCollisionExit()
	{
		mCollisionCount--;
		GetOwner()->OnCollisionExit();
	}
}