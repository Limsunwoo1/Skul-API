#include "BasicSkul.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"
#include "Application.h"

#include "Scene.h"
#include "Image.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "StateHandle.h"
#include "Shadow.h"
#include "EffectObject.h"

#include "Idle.h"
#include "Move.h"
#include "Sliding.h"
#include "Jump.h"
#include "Attack.h"
#include "Drop.h"
#include "Switch.h"
#include "ObjectProjecTile.h"

#include <iostream>


namespace sw
{
	BasicSkul::BasicSkul()
	{
		//DetaSetting
		mMaxAttackCount = 1;
		SetPos({ 5.0f, -50.0f });
		SetScale({ 5.f, 5.f });

		InitAnimtion();
		InitState();
		InitAttackCollider();
		InitSkils();

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetOwner(this);

		// main player�� �ݸ����� �޴´�
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(80.f, 80.f));
		collider->SetOwner(this);

		// ���� ������ ���� false == left
		Shadow* LShaow = new Shadow();
		LShaow->Initialize(L"L_DashShadow", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\DashEffect\\L_DashEffect.bmp");
		LShaow->SetTarget(this);
		mShadows.push_back(LShaow);

		Shadow* RShaow = new Shadow();
		RShaow->Initialize(L"R_DashShadow", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\DashEffect\\R_DashEffect.bmp");
		RShaow->SetTarget(this);
		mShadows.push_back(RShaow);

		this->SetState(ePlayerState::IDLE);
		Camera::GetInstance()->SetTarget(this);
	}

	BasicSkul::~BasicSkul()
	{
		GameObject::~GameObject();
		if(mState)
			delete mState;

		for (int i = 0; i < mShadows.size(); ++i)
			delete mShadows[i];

		mShadows.clear();
	}

	void BasicSkul::Tick()
	{
		// �ڵ� ���� �ؾ���
		if (mParentObject == nullptr)
			return;

		mState->Tick();
		GameObject::Tick();

		mDirction = mState->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		if (mShadows[mDirction])
			mShadows[mDirction]->Tick();
	}

	void BasicSkul::Render(HDC hdc)
	{
		if (mParentObject == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		pos = Camera::GetInstance()->CalculatePos(pos);

		if (mShadows[mDirction])
			mShadows[mDirction]->Render(hdc);

		GameObject::Render(hdc);

		if (mColliderBox.BoxScale != Vector2::Zero)
		{
			Vector2 pos = GetPos() + mColliderBox.BoxOffset;
			Vector2 scale= mColliderBox.BoxScale;
			
			pos = Camera::GetInstance()->CalculatePos(pos);
			HPEN oldpen = (HPEN)SelectObject(hdc, Application::GetInstance().GetPen(ePenColor::Green));
			HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));
			Rectangle(hdc, pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f)
				, pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f));
			
			SelectObject(hdc, oldpen);
			SelectObject(hdc, oldbrush);
		}
	}
	void BasicSkul::InitAnimtion()
	{
		// Animation ����
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Basic_IDLE", BASICSKUL_R_PATH(L"Idle"), Vector2(-20.f, 45.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Basic_IDLE", BASICSKUL_L_PATH(L"Idle"), Vector2(20.f, 45.f), 0.25f);

		mAnimator->CreatAnimations(L"R_Basic_RUN", BASICSKUL_R_PATH(L"RUN"), Vector2::Zero, 0.05f);
		mAnimator->CreatAnimations(L"L_Basic_RUN", BASICSKUL_L_PATH(L"RUN"), Vector2::Zero, 0.05f);

		mAnimator->CreatAnimations(L"R_Basic_JUMP", BASICSKUL_R_PATH(L"JUMP"), Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_JUMP", BASICSKUL_L_PATH(L"JUMP"), Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_Drop", BASICSKUL_R_PATH(L"Drop"), Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_Drop", BASICSKUL_L_PATH(L"Drop"), Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_Dash", BASICSKUL_R_PATH(L"Dash"), Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_Dash", BASICSKUL_L_PATH(L"Dash"), Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_AttackA", BASICSKUL_R_PATH(L"AttackA"), Vector2(-20.f, 9.f), 0.15f);
		mAnimator->CreatAnimations(L"R_Basic_AttackB", BASICSKUL_R_PATH(L"AttackB"), Vector2(-20.f, 0.f), 0.15f);

		mAnimator->CreatAnimations(L"L_Basic_AttackA", BASICSKUL_L_PATH(L"AttackA"), Vector2(20.f, 0.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Basic_AttackB", BASICSKUL_L_PATH(L"AttackB"), Vector2(20.f, 0.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Basic_Switch", BASICSKUL_R_PATH(L"Switch"), Vector2(0.f, 10.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Basic_Switch", BASICSKUL_L_PATH(L"Switch"), Vector2(0.f, 10.f), 0.1f);

		AddComponent(mAnimator);

		mAnimator->Play(L"R_Basic_IDLE", true);
		mAnimator->GetStartEvent(L"R_Basic_Dash") = std::bind(&PlayerBase::DashSmoke, this);
		mAnimator->GetStartEvent(L"L_Basic_Dash") = std::bind(&PlayerBase::DashSmoke, this);

		mAnimator->GetStartEvent(L"R_Basic_JUMP") = std::bind(&PlayerBase::JumpSmoke, this);
		mAnimator->GetStartEvent(L"L_Basic_JUMP") = std::bind(&PlayerBase::JumpSmoke, this);

		/*mAnimator->GetStartEvent(L"R_Basic_AttackA") = std::bind(&BasicSkul::AttackEffect, this);
		mAnimator->GetStartEvent(L"R_Basic_AttackB") = std::bind(&BasicSkul::AttackEffect, this);

		mAnimator->GetStartEvent(L"L_Basic_AttackA") = std::bind(&BasicSkul::AttackEffect, this);
		mAnimator->GetStartEvent(L"L_Basic_AttackB") = std::bind(&BasicSkul::AttackEffect, this);*/
		/*mAnimator->GetStartEvent(L"R_Basic_AttackA") = std::bind(&BasicSkul::R_AttackA, this);
		mAnimator->GetStartEvent(L"R_Basic_AttackB") = std::bind(&BasicSkul::R_AttackB, this);

		mAnimator->GetStartEvent(L"L_Basic_AttackA") = std::bind(&BasicSkul::L_AttackA, this);
		mAnimator->GetStartEvent(L"L_Basic_AttackB") = std::bind(&BasicSkul::L_AttackB, this);*/
		//mAnimator->StartEvent()
		// Animator �� ���� �������� �ִϸ��̼� ������ ���ε�
		//animator->StartEvent() = std::bind(&Player::StartEvent, this);
		//animator->EndEvent() = std::bind(&Player::EndEvent, this);
		/*if (mAnimator->bPlayAnimation())
		{
			mAnimator->CompleteEvent() =
				std::bind(&Player::CompleteEvent, this);
		}*/
	}
	void BasicSkul::InitState()
	{
		this->mState = new StateHandle();
		this->mState->SetTarget(this);

		Idle* idle = new Idle();
		idle->SetR_Animation(L"R_Basic_IDLE");
		idle->SetL_Animation(L"L_Basic_IDLE");

		Move* move = new Move();
		move->SetR_Animation(L"R_Basic_RUN");
		move->SetL_Animation(L"L_Basic_RUN");

		Jump* jump = new Jump();
		jump->SetR_Animation(L"R_Basic_JUMP");
		jump->SetL_Animation(L"L_Basic_JUMP");

		Sliding* sliding = new Sliding();
		sliding->SetR_Animation(L"R_Basic_Dash");
		sliding->SetL_Animation(L"L_Basic_Dash");

		Drop* drop = new Drop();
		drop->SetR_Animation(L"R_Basic_Drop");
		drop->SetL_Animation(L"L_Basic_Drop");

		Attack* attack = new Attack();
		attack->SetR_AttackSequence(L"R_Basic_AttackA");
		attack->SetR_AttackSequence(L"R_Basic_AttackB");

		attack->SetL_AttackSequence(L"L_Basic_AttackA");
		attack->SetL_AttackSequence(L"L_Basic_AttackB");

		Switch* inswitch = new Switch();
		inswitch->SetR_Animation(L"R_Basic_Switch");
		inswitch->SetL_Animation(L"L_Basic_Switch");

		mState->PushState(ePlayerState::IDLE, idle);
		mState->PushState(ePlayerState::MOVE, move);
		mState->PushState(ePlayerState::JUMP, jump);
		mState->PushState(ePlayerState::SLIDING, sliding);
		mState->PushState(ePlayerState::DROP, drop);
		mState->PushState(ePlayerState::ATTACK, attack);
		mState->PushState(ePlayerState::SWITCH, inswitch);
	}

	void BasicSkul::InitAttackCollider()
	{
		std::pair<std::wstring, Box> pair;
		Vector2 scale = Vector2::Zero;
		Vector2 offset = Vector2::Zero;

		scale = Vector2(100.f, 80.f);
		offset = Vector2(65.f, -25.f);
		SetColliders(L"R_Basic_AttackA",Box{ scale ,offset });

		scale = Vector2(100.f, 80.f);
		offset = Vector2(75.f, -25.f);
		SetColliders(L"R_Basic_AttackB", Box{ scale ,offset });

		scale = Vector2(100.f, 80.f);
		offset = Vector2(-65.f, -25.f);
		SetColliders(L"L_Basic_AttackA", Box{ scale ,offset });

		scale = Vector2(100.f, 80.f);
		offset = Vector2(-75.f, -25.f);
		SetColliders(L"L_Basic_AttackB", Box{ scale ,offset });
	}

	void BasicSkul::InitSkils()
	{
		ObjectProjecTile* SwitchProject = mSkils[(int)eSkilType::Switch];
		SwitchProject->SetEvent(std::bind(&BasicSkul::SwitchProject, this, std::placeholders::_1));
		SwitchProject->SetTarget(this);
		SwitchProject->SetReuse_Time(0.4f);
		Collider* collider = SwitchProject->GetComponent<Collider>();
		collider->SetScale(Vector2(110.f, 80.f));

		ObjectProjecTile* SkilA = mSkils[(int)eSkilType::SkilA];
		ObjectProjecTile* SkilB = mSkils[(int)eSkilType::SkilB];
	}

	void BasicSkul::SwitchSkill()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();

		if(dirction)
			rigidbody->AddForce(Vector2(200.f, 0.f));
		else
			rigidbody->AddForce(Vector2(-200.f, 0.f));
	}

	void BasicSkul::SwitchProject(GameObject* object)
	{
		Rigidbody* rgid = object->GetComponent<Rigidbody>();

		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		if (dirction)
			rgid->AddForce(Vector2(1400.f, 0.0f));
		else
			rgid->AddForce(Vector2(-1400.f, 0.0f));
	}
	void BasicSkul::OnAttackEffect(GameObject* other)
	{
		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = mEffect->GetComponent<Animator>();
		mEffect->SetDeath(false);
		mEffect->SetPos(other->GetPos());
		mEffect->SetScale(Vector2(2.0f, 2.0f));

		/*if (dirction)
			animator->Play(L"R_AttackEffect");
		else
			animator->Play(L"L_AttackEffect");*/

		animator->SetAlpha(225);
	}
}
