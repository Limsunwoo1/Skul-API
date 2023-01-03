#include "MaidMonster_1.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
namespace sw
{
	MaidMonster_1::MaidMonster_1()
		: MonsterBase()
	{
		SetHp(12);
		SetPower(1);
		InitializeAnimation();
		InitalizeCollider();
		InitializeBox();

		SetScale(Vector2(4.f, 4.f));
		mAttackX = 100;
		mAttackY = 50;

		Vector2 colscale = GetComponent<Collider>()->GetScale();
		mHpPanel->SetPos(Vector2(GetPos().x, GetPos().y - (colscale.y * 0.5f)));
		mHpPanel->SetSize(Vector2(GetHp() * 5.f, 15.f));
		mHpBar->SetSize(Vector2(GetHp() * 5.f, 8.f));
	}
	MaidMonster_1::~MaidMonster_1()
	{
		GameObject::~GameObject();
	}

	void MaidMonster_1::InitializeAnimation()
	{
		RName = L"R_MaidMonster_1";
		LName = L"L_MaidMonster_1";

		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		mAnimator->CreatAnimations(RName + L"Idle", MAIDMONSTER_1_R_PATH(L"Idle"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Idle", MAIDMONSTER_1_L_PATH(L"Idle"), Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(RName + L"Move", MAIDMONSTER_1_R_PATH(L"Move"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Move", MAIDMONSTER_1_L_PATH(L"Move"), Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(RName + L"Attack", MAIDMONSTER_1_R_PATH(L"Attack"), Vector2(0.f, 10.f), 0.25f);
		mAnimator->CreatAnimations(LName + L"Attack", MAIDMONSTER_1_L_PATH(L"Attack"), Vector2(0.f, 10.f), 0.25f);

		mAnimator->CreatAnimations(RName + L"Hit", MAIDMONSTER_1_R_PATH(L"Hit"), Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(LName + L"Hit", MAIDMONSTER_1_L_PATH(L"Hit"), Vector2::Zero, 0.15f);

		mAnimator->Play(RName + L"Idle", true);
	}

	void MaidMonster_1::InitializeBox()
	{
		mStaringCollider.BoxOffset = Vector2(0.0f, -30.f);
		mStaringCollider.BoxScale = Vector2(400.f, 50.f);

		mAttackcollider.BoxOffset = Vector2(0.0f, -30.f);
		mAttackcollider.BoxScale = Vector2(70.f, 70.f);
	}
	void MaidMonster_1::InitalizeCollider()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(100.f, 100.f));
	}
}
