#include "Wood_Monster_1.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "EventManager.h"

#include "Image.h"
#include "Collider.h"
#include "Animator.h"

namespace sw
{
	static int hp = 20;

	Wood_Monster_1::Wood_Monster_1()
		: mImage(nullptr)
	{
		SetPos(Vector2(500, 400));
		SetScale(Vector2(100, 100));

		if (!mImage)
		{
			mImage = ResourceManager::GetInstance()->Load<Image>(L"WOODMONSTER1", L"..\\Resource\\Image\\MonsterWood.bmp");
		}

		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(100.f, 100.f));

		AddComponent(new Animator());

		alpha = 255;
	}
	Wood_Monster_1::~Wood_Monster_1()
	{
		GameObject::~GameObject();
	}

	void Wood_Monster_1::Tick()
	{
		if (hp <= 0)
		{
			SetDeath(true);
		}
		if (KEY_DOWN(eKeyCode::I))
		{
			if(alpha > 0)
				alpha = 0;
			else
				alpha = 255;
		}

		GameObject::Tick();
	}

	void Wood_Monster_1::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();


		/*TransparentBlt(hdc,
			finalPos.x, finalPos.y,
			1920, 1080,
			mImage->GetDC(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(),
			RGB(255, 0, 255));*/

		pos = Camera::GetInstance()->CalculatePos(pos);

		BLENDFUNCTION bf;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = alpha;

		AlphaBlend(hdc,
			pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f),
			scale.x, scale.y,
			mImage->GetDC(),
			0, 0,
			mImage->GetWidth(), mImage->GetHeight()
			, bf);

		GameObject::Render(hdc);
	}

	void Wood_Monster_1::OnCollisionEnter(Collider* other)
	{
		
	}
	void Wood_Monster_1::OnCollisionStay(Collider* other)
	{

	}
	void Wood_Monster_1::OnCollisionExit(Collider* other)
	{

	}

	void Wood_Monster_1::OnCollisionEnter()
	{
		hp -= 2;
	}
	void Wood_Monster_1::OnCollisionStay()
	{

	}
	void Wood_Monster_1::OnCollisionExit()
	{

	}
}
