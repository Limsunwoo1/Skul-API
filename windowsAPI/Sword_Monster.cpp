#include "Sword_Monster.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
namespace sw
{
	SwordMonster::SwordMonster()
		: MonsterBase()
	{
		SetHp(12);
		SetPower(1);

		InitializeAnimation();
		InitalizeCollider();
		InitializeBox();

		SetScale(Vector2(4.f, 4.f));
		mAttackX = 100;
		mAttackY = 80;

		Vector2 colscale = GetComponent<Collider>()->GetScale();
		mHpPanel->SetPos(Vector2(GetPos().x, GetPos().y - (colscale.y * 0.5f)));
		mHpPanel->SetSize(Vector2(GetHp() * 5.f, 15.f));
		mHpBar->SetSize(Vector2(GetHp() * 5.f, 8.f));
	}
	SwordMonster::~SwordMonster()
	{
		GameObject::~GameObject();
	}

	void SwordMonster::InitializeAnimation()
	{
		RName = L"R_SwordMonster";
		LName = L"L_SwordMonster";

		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		mAnimator->CreatAnimations(RName+ L"Idle", SWORDMONSTER_R_PATH(L"Idle"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Idle", SWORDMONSTER_L_PATH(L"Idle"), Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(RName + L"Move", SWORDMONSTER_R_PATH(L"Move"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Move", SWORDMONSTER_L_PATH(L"Move"), Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(RName + L"Attack", SWORDMONSTER_R_PATH(L"Attack"), Vector2(0.f, 10.f), 0.25f);
		mAnimator->CreatAnimations(LName + L"Attack", SWORDMONSTER_L_PATH(L"Attack"), Vector2(0.f, 10.f), 0.25f);

		mAnimator->CreatAnimations(RName + L"Hit", SWORDMONSTER_R_PATH(L"Hit"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Hit", SWORDMONSTER_L_PATH(L"Hit"), Vector2::Zero, 0.15f);

		mAnimator->Play(RName + L"Idle", true);
	}

	void SwordMonster::InitializeBox()
	{
		mStaringCollider.BoxOffset = Vector2(0.0f, -30.f);
		mStaringCollider.BoxScale = Vector2(400.f, 50.f);

		mAttackcollider.BoxOffset = Vector2(0.0f, -30.f);
		mAttackcollider.BoxScale = Vector2(70.f, 70.f);
	}
	void SwordMonster::InitalizeCollider()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(100.f, 100.f));
	}
}
