#include "SwordSkul.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Collider.h"
#include "Camera.h"
#include "StateHandle.h"
#include "Idle.h"
#include "Move.h"
#include "Jump.h"
#include "Sliding.h"
#include "Drop.h"
#include "Attack.h"
#include "Switch.h"

namespace sw
{
	SwordSkul::SwordSkul()
	{
		//DetaSetting
		mMaxAttackCount = 1;
		SetPos({ 100.0f, 100.0f });
		SetScale({ 4.f, 4.f });

		InitAnimtion();
		InitState();

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(100.f, 100.f));
		collider->SetOwner(this);

		this->SetState(eObjectState::IDLE);
		Camera::GetInstance()->SetTarget(this);
	}
	SwordSkul::~SwordSkul()
	{
		GameObject::~GameObject();
		if (mState)
			delete mState;
		if (mShaow)
			delete mShaow;
	}
	void SwordSkul::Tick()
	{
		if (mParentObject == nullptr)
			return;

		GameObject::Tick();
		mState->Tick();

		if (mShaow)
			mShaow->Tick();

		Vector2 pos = GetPos();
		mParentObject->SetPos(pos);
	}
	void SwordSkul::Render(HDC hdc)
	{
		if (mParentObject == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		if (mShaow)
			mShaow->Render(hdc);

		GameObject::Render(hdc);
	}
	void SwordSkul::OnCollisionEnter(Collider* other)
	{
	}
	void SwordSkul::OnCollisionStay(Collider* other)
	{
	}
	void SwordSkul::OnCollisionExit(Collider* other)
	{
	}
	void SwordSkul::InitAnimtion()
	{
		// Animation ¼¼ÆÃ
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Sword_IDLE", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Idle", Vector2(0.f, 10.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Sword_IDLE", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Idle", Vector2(0.f, 10.f), 0.25f);

		mAnimator->CreatAnimations(L"R_Sword_Run", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Run", Vector2(0.f, 10.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Sword_Run", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Run", Vector2(0.f, 10.f), 0.1f);

		mAnimator->CreatAnimations(L"R_Sword_AttackA", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\AttackA", Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_AttackA", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\AttackA", Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_AttackB", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\AttackB", Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_AttackB", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\AttackB", Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Jump", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Jump", Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Jump", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Jump", Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Drop", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Drop", Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Drop", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Drop", Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Dash", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Dash", Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Dash", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Dash", Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Switch", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\Switch", Vector2(0.f, 33.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Switch", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\Switch", Vector2(0.f, 33.f), 0.15f);

		AddComponent(mAnimator);

		mAnimator->Play(L"R_Sword_IDLE", true);
	}
	void SwordSkul::InitState()
	{
		this->mState = new StateHandle();
		this->mState->SetTarget(this);

		Idle* idle = new Idle();
		idle->SetR_Animation(L"R_Sword_IDLE");
		idle->SetL_Animation(L"L_Sword_IDLE");

		Move* move = new Move();
		move->SetR_Animation(L"R_Sword_Run");
		move->SetL_Animation(L"L_Sword_Run");

		Jump* jump = new Jump();
		jump->SetR_Animation(L"R_Sword_Jump");
		jump->SetL_Animation(L"L_Sword_Jump");

		Sliding* sliding = new Sliding();
		sliding->SetR_Animation(L"R_Sword_Dash");
		sliding->SetL_Animation(L"L_Sword_Dash");

		Drop* drop = new Drop();
		drop->SetR_Animation(L"R_Sword_Drop");
		drop->SetL_Animation(L"L_Sword_Drop");

		Attack* attack = new Attack();
		attack->SetR_AttackSequence(L"R_Sword_AttackA");
		attack->SetR_AttackSequence(L"R_Sword_AttackB");

		attack->SetL_AttackSequence(L"L_Sword_AttackA");
		attack->SetL_AttackSequence(L"L_Sword_AttackB");

		Switch* inswitch = new Switch();
		inswitch->SetR_Animation(L"R_Sword_Switch");
		inswitch->SetL_Animation(L"L_Sword_Switch");

		mState->PushState(eObjectState::IDLE, idle);
		mState->PushState(eObjectState::LEFT, move);
		mState->PushState(eObjectState::RIGHT, move);
		mState->PushState(eObjectState::JUMP, jump);
		mState->PushState(eObjectState::SLIDING, sliding);
		mState->PushState(eObjectState::DROP, drop);
		mState->PushState(eObjectState::ATTACK, attack);
		mState->PushState(eObjectState::SWITCH, inswitch);
	}

	void SwordSkul::InitAttackCollider()
	{

	}

	void SwordSkul::SwitchSkill()
	{

	}
}