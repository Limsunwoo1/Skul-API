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
#include "Animation.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "StateHandle.h"
#include "Shadow.h"
#include "AttackCollider.h"

#include "Idle.h"
#include "Move.h"
#include "Sliding.h"
#include "Jump.h"
#include "Attack.h"
#include "Drop.h"
#include "Switch.h"


namespace sw
{
	BasicSkul::BasicSkul()
	{
		//DetaSetting
		mMaxAttackCount = 1;
		SetPos({ 100.0f, 100.0f });
		SetScale({ 5.f, 5.f });

		InitAnimtion();
		InitState();
		InitAttackCollider();

		// main player에 콜리젼을 받는다
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(100.f, 100.f));
		collider->SetOwner(this);

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetOwner(this);

		mShaow = new Shadow();
		mShaow->Initialize(L"R_DashEffect", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\DashEffect\\R_DashEffect.bmp");
		mShaow->SetTarget(this);

		this->SetState(eObjectState::IDLE);
		Camera::GetInstance()->SetTarget(this);
	}

	BasicSkul::~BasicSkul()
	{
		GameObject::~GameObject();
		if(mState)
			delete mState;
		if(mShaow)
			delete mShaow;
	}

	void BasicSkul::Tick()
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

	void BasicSkul::Render(HDC hdc)
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

	void BasicSkul::OnCollisionEnter(Collider* other)
	{
	}
	void BasicSkul::OnCollisionStay(Collider* other)
	{
	}
	void BasicSkul::OnCollisionExit(Collider* other)
	{
	}
	void BasicSkul::InitAnimtion()
	{
		// Animation 세팅
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Basic_IDLE", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\Idle", Vector2(-20.f, 0.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Basic_IDLE", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\Idle", Vector2(20.f, 0.f), 0.3f);

		mAnimator->CreatAnimations(L"R_Basic_RUN", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\RUN", Vector2::Zero, 0.05f);
		mAnimator->CreatAnimations(L"L_Basic_RUN", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\RUN", Vector2::Zero, 0.05f);

		mAnimator->CreatAnimations(L"R_Basic_JUMP", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\JUMP", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_JUMP", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\JUMP", Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_Drop", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\Drop", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_Drop", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\Drop", Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_Dash", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\Dash", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Basic_Dash", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\Dash", Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Basic_AttackA", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\AttackA", Vector2(-20.f, 9.f), 0.15f);
		mAnimator->CreatAnimations(L"R_Basic_AttackB", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\AttackB", Vector2(-20.f, 0.f), 0.15f);

		mAnimator->CreatAnimations(L"L_Basic_AttackA", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\AttackA", Vector2(20.f, 0.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Basic_AttackB", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\AttackB", Vector2(20.f, 0.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Basic_Switch", L"..\\Resource\\Animation\\BasicSkul\\R_Basic\\Switch", Vector2(0.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Basic_Switch", L"..\\Resource\\Animation\\BasicSkul\\L_Basic\\Switch", Vector2(0.f, 0.f), 0.1f);

		AddComponent(mAnimator);

		mAnimator->Play(L"R_Basic_IDLE", true);

		/*mAnimator->GetStartEvent(L"R_Basic_AttackA") = std::bind(&BasicSkul::R_AttackA, this);
		mAnimator->GetStartEvent(L"R_Basic_AttackB") = std::bind(&BasicSkul::R_AttackB, this);

		mAnimator->GetStartEvent(L"L_Basic_AttackA") = std::bind(&BasicSkul::L_AttackA, this);
		mAnimator->GetStartEvent(L"L_Basic_AttackB") = std::bind(&BasicSkul::L_AttackB, this);*/
		//mAnimator->StartEvent()
		// Animator 에 현재 진행중인 애니메이션 셋팅후 바인딩
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

		mState->PushState(eObjectState::IDLE, idle);
		mState->PushState(eObjectState::LEFT, move);
		mState->PushState(eObjectState::RIGHT, move);
		mState->PushState(eObjectState::JUMP, jump);
		mState->PushState(eObjectState::SLIDING, sliding);
		mState->PushState(eObjectState::DROP, drop);
		mState->PushState(eObjectState::ATTACK, attack);
		mState->PushState(eObjectState::SWITCH, inswitch);
	}

	void BasicSkul::InitAttackCollider()
	{
		std::pair<std::wstring, Box> pair;
		Vector2 scale = Vector2::Zero;
		Vector2 offset = Vector2::Zero;

		scale = Vector2(80.f, 80.f);
		offset = Vector2(65.f, -25.f);
		SetColliders(L"R_Basic_AttackA",Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(75.f, -25.f);
		SetColliders(L"R_Basic_AttackB", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-65.f, -25.f);
		SetColliders(L"L_Basic_AttackA", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-75.f, -25.f);
		SetColliders(L"L_Basic_AttackB", Box{ scale ,offset });
	}

	void BasicSkul::SwitchSkill()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		rigidbody->AddForce(Vector2(200.f, 0.f));
	}
}
