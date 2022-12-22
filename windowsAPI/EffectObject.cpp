#include "EffectObject.h"
#include "Collider.h"
#include "Camera.h"
#include "Animator.h"
#include "EventManager.h"
#include "ObjectManager.h"

namespace sw
{
	EffectObject::EffectObject()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);
		InitAnimation();
		SetDeath(true);
	}

	EffectObject::~EffectObject()
	{
		GameObject::~GameObject();
	}

	void EffectObject::Tick()
	{
		if (IsDeath())
			return;
		if (mAnimator != nullptr)
		{
			if (mAnimator->bPlayAnimation() && mAnimator->isComplete())
			{
				ObjectManager::GetInstance()->PushEffectObject(this);

				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::EFFECT);
				info.Parameter2 = this;

				EventManager::GetInstance()->EventPush(info);
			}
		}

		GameObject::Tick();
	}

	void EffectObject::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		GameObject::Render(hdc);
	}

	void EffectObject::InitAnimation()
	{
		// ���� ����
		// �뽬 ����ũ
		mAnimator->CreatAnimations(L"R_DashSmoke", L"..\\Resource\\Animation\\Effect\\R_DashSmoke", Vector2(65.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"L_DashSmoke", L"..\\Resource\\Animation\\Effect\\L_DashSmoke", Vector2(-65.f, 0.f), 0.1f);
		// ��������ũ
		mAnimator->CreatAnimations(L"JumpSmoke", L"..\\Resource\\Animation\\Effect\\JumpSmoke", Vector2(0.f, -40.f), 0.05f);

		// �⺻���� ���ݽ� �ǰ� ����Ʈ
		std::wstring path = L"..\\Resource\\Animation\\Effect\\";
		mAnimator->CreatAnimations(L"L_BasicSkul_HitEft", path + L"L_BasicSkul_HitEffect",Vector2::Zero, 0.05f);
		mAnimator->CreatAnimations(L"R_BasicSkul_HitEft", path + L"R_BasicSkul_HitEffect", Vector2::Zero, 0.05f);

		// �ҵ彺�� ������ ����Ʈ
		mAnimator->CreatAnimations(L"L_SwordSkul_SlashEft", L"..\\Resource\\Animation\\Effect\\L_SkeletonSwordSlashEffect");
		mAnimator->CreatAnimations(L"R_SwordSkul_SlashEft", L"..\\Resource\\Animation\\Effect\\R_SkeletonSwordSlashEffect");

	}
}