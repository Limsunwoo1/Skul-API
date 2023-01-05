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
#include "SkilA.h"
#include "SkilB.h"
#include "Application.h"
#include "Shadow.h"
#include "ObjectProjecTile.h"
#include "Time.h"
#include "MonsterBase.h"

namespace sw
{
	SwordSkul::SwordSkul()
	{
		//DetaSetting
		SetPower(4);

		mMaxAttackCount = 2;
		SetScale({ 4.f, 4.f });

		InitAnimtion();
		InitState();
		InitAttackCollider();
		InitSkils();

		Rigidbody* rigidbody = AddComponent<Rigidbody>();
		rigidbody->SetGround(false);
		rigidbody->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(80.f, 80.f));
		collider->SetOwner(this);

		// 왼쪽 쉐도우 먼저 false == left
		Shadow* LShaow = new Shadow();
		LShaow->SetOffset(Vector2(-50.f, 0));
		LShaow->SetScale(Vector2(4.f, 4.f));
		LShaow->Initialize(L"L_Sword_DashShadow", L"..\\Resource\\Animation\\SwordSkul\\L_Sword\\DashEffect\\Dash_0.bmp");
		LShaow->SetTarget(this);
		mShadows.push_back(LShaow);

		Shadow* RShaow = new Shadow();
		RShaow->SetOffset(Vector2(50.f, 0));
		RShaow->SetScale(Vector2(4.f, 4.f));
		RShaow->Initialize(L"R_Sword_DashShadow", L"..\\Resource\\Animation\\SwordSkul\\R_Sword\\DashEffect\\Dash_0.bmp");
		RShaow->SetTarget(this);
		mShadows.push_back(RShaow);

		this->SetState(ePlayerState::IDLE);
		Camera::GetInstance()->SetTarget(this);

		// UiImage
		mHeadImage = new HUD(eUIType::Character);
		mHeadImage->SetSize(Vector2(3.0f, 3.0f));
		mHeadImage->ImageLoad(L"SwordSkulHeadImage", L"..\\Resource\\Animation\\HeadUi\\HeadUI\\Skeleton_Sword_4 #55412 복사.bmp");
	}
	SwordSkul::~SwordSkul()
	{
		GameObject::~GameObject();
		if (mState)
			delete mState;

		for (int i = 0; i < mShadows.size(); ++i)
			delete mShadows[i];

		mShadows.clear();
	}
	void SwordSkul::Tick()
	{
		SetHp(mParentObject->GetHp());
		if (GetHp() <= 0)
			SetHp(0);

		if (mParentObject == nullptr)
			return;

		mState->Tick();
		GameObject::Tick();
		if (mShadows[mSlidingDirction])
			mShadows[mSlidingDirction]->Tick();
	}
	void SwordSkul::Render(HDC hdc)
	{
		if (mParentObject == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		if (mShadows[mSlidingDirction])
			mShadows[mSlidingDirction]->Render(hdc);

		GameObject::Render(hdc);

		return;
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
		// Animation 세팅
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Sword_IDLE", SWORDSKUL_R_PATH(L"Idle"), Vector2(0.f, 60.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Sword_IDLE", SWORDSKUL_L_PATH(L"Idle"), Vector2(0.f, 60.f), 0.25f);

		mAnimator->CreatAnimations(L"R_Sword_Run", SWORDSKUL_R_PATH(L"Run"), Vector2(0.f, 10.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Sword_Run", SWORDSKUL_L_PATH(L"Run"), Vector2(0.f, 10.f), 0.1f);

		mAnimator->CreatAnimations(L"R_Sword_AttackA", SWORDSKUL_R_PATH(L"AttackA"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"R_Sword_AttackB", SWORDSKUL_R_PATH(L"AttackB"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"R_Sword_AttackC", SWORDSKUL_R_PATH(L"AttackC"), Vector2(-30.f, 10.f), 0.07f);

		mAnimator->CreatAnimations(L"L_Sword_AttackA", SWORDSKUL_L_PATH(L"AttackA"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"L_Sword_AttackB", SWORDSKUL_L_PATH(L"AttackB"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"L_Sword_AttackC", SWORDSKUL_L_PATH(L"AttackC"), Vector2(30.f, 10.f), 0.07f);

		mAnimator->CreatAnimations(L"R_Sword_Jump", SWORDSKUL_R_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Jump", SWORDSKUL_L_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Drop", SWORDSKUL_R_PATH(L"Drop"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Drop", SWORDSKUL_L_PATH(L"Drop"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Dash", SWORDSKUL_R_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Dash", SWORDSKUL_L_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_Switch", SWORDSKUL_R_PATH(L"Switch"), Vector2(0.f, 35.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Sword_Switch", SWORDSKUL_L_PATH(L"Switch"), Vector2(0.f, 35.f), 0.15f);

		mAnimator->CreatAnimations(L"R_Sword_SkilA", SWORDSKUL_R_PATH(L"SkilA"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"L_Sword_SkilA", SWORDSKUL_L_PATH(L"SkilA"), Vector2(0.f, 10.f), 0.07f);

		mAnimator->CreatAnimations(L"R_Sword_SkilB", SWORDSKUL_R_PATH(L"SkilB"), Vector2(0.f, 10.f), 0.03f);
		mAnimator->CreatAnimations(L"L_Sword_SkilB", SWORDSKUL_L_PATH(L"SkilB"), Vector2(0.f, 10.f), 0.03f);

		AddComponent(mAnimator);

		mAnimator->Play(L"R_Sword_IDLE", true);

		mAnimator->GetStartEvent(L"R_Sword_Dash") = std::bind(&PlayerBase::DashSmoke, this);
		mAnimator->GetStartEvent(L"L_Sword_Dash") = std::bind(&PlayerBase::DashSmoke, this);

		mAnimator->GetStartEvent(L"R_Sword_Jump") = std::bind(&PlayerBase::JumpSmoke, this);
		mAnimator->GetStartEvent(L"L_Sword_Jump") = std::bind(&PlayerBase::JumpSmoke, this);
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
		attack->SetSkul(eSkulHead::Sword);
		attack->SetR_AttackSequence(L"R_Sword_AttackA");
		attack->SetR_AttackSequence(L"R_Sword_AttackB");
		attack->SetR_AttackSequence(L"R_Sword_AttackC");

		attack->SetL_AttackSequence(L"L_Sword_AttackA");
		attack->SetL_AttackSequence(L"L_Sword_AttackB");
		attack->SetL_AttackSequence(L"L_Sword_AttackC");

		Switch* inswitch = new Switch();
		inswitch->SetSkul(eSkulHead::Sword);
		inswitch->SetR_Animation(L"R_Sword_Switch");
		inswitch->SetL_Animation(L"L_Sword_Switch");

		SkilA* skilA = new SkilA();
		skilA->SetSkul(eSkulHead::Sword);
		skilA->SetR_Animation(L"R_Sword_SkilA");
		skilA->SetL_Animation(L"L_Sword_SkilA");

		SkilB* skilB = new SkilB();
		skilB->SetSkul(eSkulHead::Sword);
		skilB->SetR_Animation(L"R_Sword_SkilB");
		skilB->SetL_Animation(L"L_Sword_SkilB");

		mState->PushState(ePlayerState::IDLE, idle);
		mState->PushState(ePlayerState::MOVE, move);
		mState->PushState(ePlayerState::JUMP, jump);
		mState->PushState(ePlayerState::SLIDING, sliding);
		mState->PushState(ePlayerState::DROP, drop);
		mState->PushState(ePlayerState::ATTACK, attack);
		mState->PushState(ePlayerState::SWITCH, inswitch);
		mState->PushState(ePlayerState::SKILL_A, skilA);
		mState->PushState(ePlayerState::SKILL_B, skilB);
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

	void SwordSkul::InitSkils()
	{
		// 프로젝타일 세팅
		ObjectProjecTile* SwitchProjec = mSkils[(int)eSkilType::Switch];
		SwitchProjec->SetScale(Vector2(3.0f, 3.0f));
		SwitchProjec->SetEvent(std::bind(&SwordSkul::SwitchProjecTile, this, std::placeholders::_1));
		SwitchProjec->SetTarget(this);
		SwitchProjec->SetReuse_Time(0.1f);
		SwitchProjec->SetEffectName(L"Sword_Switch_Eft");

		Collider* collider1 = SwitchProjec->GetComponent<Collider>();
		collider1->SetScale(Vector2(280.f, 70.f));
		Animator* animator1 = SwitchProjec->GetComponent<Animator>();
		animator1->CreatAnimations(SwitchProjec->GetEffectName(), L"..\\Resource\\Animation\\Effect\\SkeletonSword-Switch",Vector2::Zero, 0.03f);
		animator1->SetAlpha(180);

		// 스킬 A 세팅
		ObjectProjecTile* SkilA = mSkils[(int)eSkilType::SkilA];
		SkilA->SetScale(Vector2(5.0f, 3.0f));
		SkilA->SetEvent(std::bind(&SwordSkul::SkilAProjecTile, this, std::placeholders::_1));
		SkilA->SetTarget(this);
		SkilA->SetReuse_Time(0.1f);
		SkilA->SetEffectName(L"_Sword_SkilA_Eft");
		SkilA->SetOffset(Vector2(120.f, 0.f));
		Collider* collider2 = SkilA->GetComponent<Collider>();
		collider2->SetScale(Vector2(240.f, 70.f));
		Animator* animator2 = SkilA->GetComponent<Animator>();
		animator2->CreatAnimations(L"L_Sword_SkilA_Eft", L"..\\Resource\\Animation\\Effect\\L_SkeletonSwordSlashEffect",Vector2::Zero, 0.03f);
		animator2->CreatAnimations(L"R_Sword_SkilA_Eft", L"..\\Resource\\Animation\\Effect\\R_SkeletonSwordSlashEffect", Vector2::Zero, 0.03f);
		animator2->SetAlpha(255);
		//스킬 B 세팅
		ObjectProjecTile* SkilB = mSkils[(int)eSkilType::SkilB];
		SkilB->SetScale(Vector2(5.0f, 3.0f));
		SkilB->SetEvent(std::bind(&SwordSkul::SkilBProjecTile, this, std::placeholders::_1));
		SkilB->SetTarget(this);
		SkilB->SetReuse_Time(1.0f);
		SkilB->SetEffectName(L"_Sword_SkilB_Eft");
		SkilB->SetOffset(Vector2(200.f, 0.f));
		SkilB->SetNotMove(true);
		Collider* collider3 = SkilB->GetComponent<Collider>();
		collider3->SetScale(Vector2(300.f, 70.f));
		Animator* animator3 = SkilB->GetComponent<Animator>();
		animator3->CreatAnimations(L"L_Sword_SkilB_Eft", L"..\\Resource\\Animation\\Effect\\L_SkiletonSwordPierceEffect");
		animator3->CreatAnimations(L"R_Sword_SkilB_Eft"
			, L"..\\Resource\\Animation\\Effect\\R_SkiletonSwordPierceEffect"
			, Vector2(0.f,0.f), 0.07);
		animator3->SetAlpha(255);
	}

	void SwordSkul::OnAttackEffect(GameObject* other)
	{

	}
	void SwordSkul::SwitchProjecTile(GameObject* object)
	{
		MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
		if (monster == nullptr)
			return;
		if (monster->GetSuperArmer())
		{
			monster->Hit();
			return;
		}
		eMonsterState type = monster->GetState();
		if (type != eMonsterState::HIT)
		{
			monster->SetAble(type, false);
			monster->SetState(eMonsterState::HIT);
		}
	}

	void SwordSkul::SkilAProjecTile(GameObject* object)
	{
		MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
		if (monster == nullptr)
			return;
		if (monster->GetSuperArmer())
		{
			monster->Hit();
			return;
		}
		eMonsterState type = monster->GetState();
		if (type != eMonsterState::HIT)
		{
			monster->SetAble(type, false);
			monster->SetState(eMonsterState::HIT);
		}
	}

	void SwordSkul::SkilBProjecTile(GameObject* object)
	{
		MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
		if (monster == nullptr)
			return;
		if (monster->GetSuperArmer())
		{
			monster->Hit();
			return;
		}
		eMonsterState type = monster->GetState();
		if (type != eMonsterState::HIT)
		{
			monster->SetAble(type, false);
			monster->SetState(eMonsterState::HIT);
		}
	}

	void SwordSkul::OnSkilB()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		if (mArrivalPos == Vector2::Zero)
		{
			mArrivalPos = GetPos();
			if(dirction)
				mArrivalPos.x += 300;
			else
				mArrivalPos.x -= 300;

			rigidbody->SetVelocity(Vector2::Zero);
		}

		if (dirction)
		{
			if(mArrivalPos.x > GetPos().x)
				rigidbody->AddForce(Vector2(4000.f, 0.0f));
		}
		else
		{
			if(mArrivalPos.x < GetPos().x)
				rigidbody->AddForce(Vector2(-4000.f, 0.0f));
		}


		if (GetComponent<Animator>()->isComplete())
			mArrivalPos = Vector2::Zero;
	}
}