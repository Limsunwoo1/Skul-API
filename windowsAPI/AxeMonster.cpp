#include "AxeMonster.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
namespace sw
{
	AxeMonster::AxeMonster()
		: MonsterBase()
	{
		InitializeAnimation();
		InitalizeCollider();
		InitializeBox();

		SetScale(Vector2(5.f, 5.f));
		mAttackX = 300;
		mAttackY = 200;
		mArmer = true;

		mAttackCooltimeMax = 3.0f;
	}
	AxeMonster::~AxeMonster()
	{
		GameObject::~GameObject();
	}

	void AxeMonster::InitializeAnimation()
	{
		RName = L"R_AxeMonster";
		LName = L"L_AxeMonster";

		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		mAnimator->CreatAnimations(RName + L"Idle", AXEMONSTER_R_PATH(L"Idle"), Vector2(0.0f, -23.f), 0.1f);
		mAnimator->CreatAnimations(LName + L"Idle", AXEMONSTER_L_PATH(L"Idle"), Vector2(0.0f, -23.f), 0.1f);

		mAnimator->CreatAnimations(RName + L"Move", AXEMONSTER_R_PATH(L"Move"), Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(LName + L"Move", AXEMONSTER_L_PATH(L"Move"), Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(RName + L"Attack", AXEMONSTER_R_PATH(L"Attack"), Vector2(0.f, 0.f), 0.5f);
		mAnimator->CreatAnimations(LName + L"Attack", AXEMONSTER_L_PATH(L"Attack"), Vector2(0.f, 0.f), 0.5f);

		mAnimator->Play(RName + L"Idle", true);
	}

	void AxeMonster::InitializeBox()
	{
		mStaringCollider.BoxOffset = Vector2(0.0f, -30.f);
		mStaringCollider.BoxScale = Vector2(400.f, 200.f);

		mAttackcollider.BoxOffset = Vector2(0.0f, -30.f);
		mAttackcollider.BoxScale = Vector2(200.f, 200.f);
	}
	void AxeMonster::InitalizeCollider()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(300.f, 250.f));
	}
	void AxeMonster::Hit()
	{
		// hp °¨¼Ò
	}
}
