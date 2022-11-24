#include "Meteor.h"
#include "Time.h"
#include "Camera.h"

#include "Animator.h"
#include "Collider.h"

namespace sw
{
	const Vector2D Gravity = { 0.0f, 9.8f };

	Meteor::Meteor()
		: speed ({ 0.0f, 1.0f })
	{
		SetScale({ 50.f,50.f });
	}

	Meteor::~Meteor()
	{
		GameObject::~GameObject();
	}

	void Meteor::Tick()
	{
		GameObject::Tick();

		float delta = Time::GetInstance()->DeltaTime();
		Vector2D pos = GetPos();

		if (pos.y > 1080)
			return;
		speed += Gravity * delta;
		pos += speed * delta * 50;

		SetPos(pos);
	}

	void Meteor::Render(HDC hdc)
	{
		Vector2D pos = GetPos();
		Vector2D scale = GetScale();
		
		pos = Camera::GetInstance()->CalculatePos(pos);

		Ellipse(hdc, pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f),
			pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f));

		GameObject::Render(hdc);
	}
	void Meteor::OnCollisionEnter(Collider* other)
	{
	}
	void Meteor::OnCollisionStay(Collider* other)
	{
	}
	void Meteor::OnCollisionExit(Collider* other)
	{
	}
}