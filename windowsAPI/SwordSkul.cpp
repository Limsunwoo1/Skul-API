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
#include "Application.h"
#include "Shadow.h"
#include <iostream>

namespace sw
{
	SwordSkul::SwordSkul()
	{
		//DetaSetting
		mMaxAttackCount = 2;
		SetPos({ 100.0f, 100.0f });
		SetScale({ 4.f, 4.f });

		InitAnimtion();
		InitState();
		InitAttackCollider();

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(100.f, 100.f));
		collider->SetOwner(this);

		this->SetState(ePlayerState::IDLE);
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

		mState->Tick();
		GameObject::Tick();

		if (mShaow)
			mShaow->Tick();
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

		if (mColliderBox.BoxScale != Vector2::Zero)
		{

			Vector2 pos = GetPos() + mColliderBox.BoxOffset;
			Vector2 scale = mColliderBox.BoxScale;

			pos = Camera::GetInstance()->CalculatePos(pos);
			HPEN oldpen = (HPEN)SelectObject(hdc, Application::GetInstance().GetPen(ePenColor::Green));
			HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));
			Rectangle(hdc, pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f)
				, pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f));

			SelectObject(hdc, oldpen);
			SelectObject(hdc, oldbrush);
		}
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
		// Animation ����
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Sword_IDLE", SWORDSKUL_R_PATH(L"Idle"), Vector2(0.f, 50.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Sword_IDLE", SWORDSKUL_L_PATH(L"Idle"), Vector2(0.f, 50.f), 0.25f);

		mAnimator->CreatAnimations(L"R_Sword_Run", SWORDSKUL_R_PATH(L"Run"), Vector2(0.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Sword_Run", SWORDSKUL_L_PATH(L"Run"), Vector2(0.f, 0.f), 0.1f);

		mAnimator->CreatAnimations(L"R_Sword_AttackA", SWORDSKUL_R_PATH(L"AttackA"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"R_Sword_AttackB", SWORDSKUL_R_PATH(L"AttackB"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"R_Sword_AttackC", SWORDSKUL_R_PATH(L"AttackC"), Vector2(-30.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"L_Sword_AttackA", SWORDSKUL_L_PATH(L"AttackA"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_AttackB", SWORDSKUL_L_PATH(L"AttackB"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_AttackC", SWORDSKUL_L_PATH(L"AttackC"), Vector2(30.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Jump", SWORDSKUL_R_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Jump", SWORDSKUL_L_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Drop", SWORDSKUL_R_PATH(L"Drop"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Drop", SWORDSKUL_L_PATH(L"Drop"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Dash", SWORDSKUL_R_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Dash", SWORDSKUL_L_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Switch", SWORDSKUL_R_PATH(L"Switch"), Vector2(0.f, 25.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Switch", SWORDSKUL_L_PATH(L"Switch"), Vector2(0.f, 25.f), 0.15f);

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
		attack->SetR_AttackSequence(L"R_Sword_AttackC");

		attack->SetL_AttackSequence(L"L_Sword_AttackA");
		attack->SetL_AttackSequence(L"L_Sword_AttackB");
		attack->SetL_AttackSequence(L"L_Sword_AttackC");

		Switch* inswitch = new Switch();
		inswitch->SetR_Animation(L"R_Sword_Switch");
		inswitch->SetL_Animation(L"L_Sword_Switch");

		mState->PushState(ePlayerState::IDLE, idle);
		mState->PushState(ePlayerState::MOVE, move);
		mState->PushState(ePlayerState::JUMP, jump);
		mState->PushState(ePlayerState::SLIDING, sliding);
		mState->PushState(ePlayerState::DROP, drop);
		mState->PushState(ePlayerState::ATTACK, attack);
		mState->PushState(ePlayerState::SWITCH, inswitch);
	}

	void SwordSkul::InitAttackCollider()
	{
		std::pair<std::wstring, Box> pair;
		Vector2 scale = Vector2::Zero;
		Vector2 offset = Vector2::Zero;

		scale = Vector2(80.f, 80.f);
		offset = Vector2(65.f, -25.f);
		SetColliders(L"R_Sword_AttackA", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(75.f, -25.f);
		SetColliders(L"R_Sword_AttackB", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(85.f, -25.f);
		SetColliders(L"R_Sword_AttackC", Box{ scale ,offset });

		////////////////////////////////////////////////////////

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-65.f, -25.f);
		SetColliders(L"L_Sword_AttackA", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-75.f, -25.f);
		SetColliders(L"L_Sword_AttackB", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-85.f, -25.f);
		SetColliders(L"L_Sword_AttackC", Box{ scale ,offset });
	}

	void SwordSkul::SwitchSkill()
	{

	}
	void SwordSkul::DashEffect()
	{
	}
	void SwordSkul::OnAttackEffect(GameObject* other)
	{

	}
}