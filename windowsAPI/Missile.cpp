#include "Missile.h"
#include "Time.h"


sw::Missile::Missile()
	: mSpeed(1.0f)
{
	SetPos({ 100.0f,100.0f });
	SetScale({ 50.0f, 50.0f });
}

sw::Missile::~Missile()
{
	GameObject::~GameObject();
}

void sw::Missile::Tick()
{
	Vector2D pos = GetPos();

	pos.y -= 500.0f * Time::GetInstance()->DeltaTime();

	SetPos(pos);
}

void sw::Missile::Render(HDC hdc)
{
	Vector2D pos = GetPos();
	Vector2D scale = GetScale();

	Ellipse(hdc, pos.x, pos.y, pos.x + scale.x, pos.y + scale.y);
}
