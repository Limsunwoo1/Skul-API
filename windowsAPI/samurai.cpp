#include "samurai.h"
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
	Samurai::Samurai()
	{
		//DetaSetting
		SetPower(4);

		mMaxAttackCount = 2;
		SetPos({ 100.0f, 100.0f });
		SetScale({ 5.f, 5.f });

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
		mHeadImage->ImageLoad(L"SamuraiHeadImage", L"..\\Resource\\Animation\\HeadUi\\HeadUI\\Samurai #55982 복사.bmp");
	}
	Samurai::~Samurai()
	{
		GameObject::~GameObject();
		if (mState)
			delete mState;

		for (int i = 0; i < mShadows.size(); ++i)
			delete mShadows[i];

		mShadows.clear();
	}
	void Samurai::Tick()
	{
		SetHp(mParentObject->GetHp());
		if (GetHp() < 0)
			SetDeath(true);

		if (mParentObject == nullptr)
			return;

		mState->Tick();
		GameObject::Tick();

		if (mShadows[mSlidingDirction])
			mShadows[mSlidingDirction]->Tick();
	}
	void Samurai::Render(HDC hdc)
	{
		if (mParentObject == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();
		pos = Camera::GetInstance()->CalculatePos(pos);

		if (mShadows[mSlidingDirction])
			mShadows[mSlidingDirction]->Render(hdc);

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
	void Samurai::OnCollisionEnter(Collider* other)
	{
	}
	void Samurai::OnCollisionStay(Collider* other)
	{
	}
	void Samurai::OnCollisionExit(Collider* other)
	{
	}
	void Samurai::InitAnimtion()
	{
		// Animation 세팅
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_Samurai_IDLE", SAMURAI_R_PATH(L"Idle"), Vector2(0.f, 0.f), 0.25f);
		mAnimator->CreatAnimations(L"L_Samurai_IDLE", SAMURAI_L_PATH(L"Idle"), Vector2(0.f,0.f), 0.25f);
										
		mAnimator->CreatAnimations(L"R_Samurai_Run", SAMURAI_R_PATH(L"Walk"), Vector2(0.f, 10.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Samurai_Run", SAMURAI_L_PATH(L"Walk"), Vector2(0.f, 10.f), 0.1f);
										
		mAnimator->CreatAnimations(L"R_Samurai_AttackA", SAMURAI_R_PATH(L"AttackA"), Vector2(0.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"R_Samurai_AttackB", SAMURAI_R_PATH(L"AttackB"), Vector2(-30.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"R_Samurai_AttackC", SAMURAI_R_PATH(L"AttackC"), Vector2(-30.f, 0.f), 0.1f);
										
		mAnimator->CreatAnimations(L"L_Samurai_AttackA", SAMURAI_L_PATH(L"AttackA"), Vector2(0.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Samurai_AttackB", SAMURAI_L_PATH(L"AttackB"), Vector2(30.f, 0.f), 0.1f);
		mAnimator->CreatAnimations(L"L_Samurai_AttackC", SAMURAI_L_PATH(L"AttackC"), Vector2(30.f, 0.f), 0.1f);
										
		mAnimator->CreatAnimations(L"R_Samurai_Jump", SAMURAI_R_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Samurai_Jump", SAMURAI_L_PATH(L"Jump"), Vector2(0.f, 10.f), 0.15f);
										
		mAnimator->CreatAnimations(L"R_Samurai_Drop", SAMURAI_R_PATH(L"FallRepeat"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Samurai_Drop", SAMURAI_L_PATH(L"FallRepeat"), Vector2(0.f, 10.f), 0.15f);
										
		mAnimator->CreatAnimations(L"R_Samurai_Dash", SAMURAI_R_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Samurai_Dash", SAMURAI_L_PATH(L"Dash"), Vector2(0.f, 10.f), 0.15f);
										
		mAnimator->CreatAnimations(L"R_Samurai_Switch", SAMURAI_R_PATH(L"Switch"), Vector2(0.f, 30.f), 0.15f);
		mAnimator->CreatAnimations(L"L_Samurai_Switch", SAMURAI_L_PATH(L"Switch"), Vector2(0.f, 30.f), 0.15f);
										
		mAnimator->CreatAnimations(L"R_Samurai_SkilA", SAMURAI_R_PATH(L"Skill"), Vector2(0.f, 10.f), 0.07f);
		mAnimator->CreatAnimations(L"L_Samurai_SkilA", SAMURAI_L_PATH(L"Skill"), Vector2(0.f, 10.f), 0.07f);
										
		mAnimator->CreatAnimations(L"R_Samurai_SkilB", SAMURAI_R_PATH(L"Skill2"), Vector2(0.f, 10.f), 0.03f);
		mAnimator->CreatAnimations(L"L_Samurai_SkilB", SAMURAI_L_PATH(L"Skill2"), Vector2(0.f, 10.f), 0.03f);

		AddComponent(mAnimator);

		mAnimator->Play(L"R_Samurai_IDLE", true);

		//mAnimator->GetStartEvent(L"R_Sword_Dash") = std::bind(&PlayerBase::DashSmoke, this);
		//mAnimator->GetStartEvent(L"L_Sword_Dash") = std::bind(&PlayerBase::DashSmoke, this);
		//
		//mAnimator->GetStartEvent(L"R_Sword_Jump") = std::bind(&PlayerBase::JumpSmoke, this);
		//mAnimator->GetStartEvent(L"L_Sword_Jump") = std::bind(&PlayerBase::JumpSmoke, this);
	}
	void Samurai::InitState()
	{
		this->mState = new StateHandle();
		this->mState->SetTarget(this);

		Idle* idle = new Idle();
		idle->SetR_Animation(L"R_Samurai_IDLE");
		idle->SetL_Animation(L"L_Samurai_IDLE");

		Move* move = new Move();
		move->SetR_Animation(L"R_Samurai_Run");
		move->SetL_Animation(L"L_Samurai_Run");

		Jump* jump = new Jump();
		jump->SetR_Animation(L"R_Samurai_Jump");
		jump->SetL_Animation(L"L_Samurai_Jump");

		Sliding* sliding = new Sliding();
		sliding->SetR_Animation(L"R_Samurai_Dash");
		sliding->SetL_Animation(L"L_Samurai_Dash");

		Drop* drop = new Drop();
		drop->SetR_Animation(L"R_Samurai_Drop");
		drop->SetL_Animation(L"L_Samurai_Drop");

		Attack* attack = new Attack();
		attack->SetR_AttackSequence(L"R_Samurai_AttackA");
		attack->SetR_AttackSequence(L"R_Samurai_AttackB");
		attack->SetR_AttackSequence(L"R_Samurai_AttackC");

		attack->SetL_AttackSequence(L"L_Samurai_AttackA");
		attack->SetL_AttackSequence(L"L_Samurai_AttackB");
		attack->SetL_AttackSequence(L"L_Samurai_AttackC");

		Switch* inswitch = new Switch();
		inswitch->SetR_Animation(L"R_Samurai_Switch");
		inswitch->SetL_Animation(L"L_Samurai_Switch");

		SkilA* skilA = new SkilA();
		skilA->SetR_Animation(L"R_Samurai_SkilA");
		skilA->SetL_Animation(L"L_Samurai_SkilA");

		SkilB* skilB = new SkilB();
		skilB->SetR_Animation(L"R_Samurai_SkilB");
		skilB->SetL_Animation(L"L_Samurai_SkilB");

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

	void Samurai::InitAttackCollider()
	{
		std::pair<std::wstring, Box> pair;
		Vector2 scale = Vector2::Zero;
		Vector2 offset = Vector2::Zero;

		scale = Vector2(80.f, 80.f);
		offset = Vector2(65.f, -25.f);
		SetColliders(L"R_Samurai_AttackA", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(75.f, -25.f);
		SetColliders(L"R_Samurai_AttackB", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(85.f, -25.f);
		SetColliders(L"R_Samurai_AttackC", Box{ scale ,offset });

		////////////////////////////////////////////////////////

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-65.f, -25.f);
		SetColliders(L"L_Samurai_AttackA", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-75.f, -25.f);
		SetColliders(L"L_Samurai_AttackB", Box{ scale ,offset });

		scale = Vector2(80.f, 80.f);
		offset = Vector2(-85.f, -25.f);
		SetColliders(L"L_Samurai_AttackC", Box{ scale ,offset });
	}

	void Samurai::InitSkils()
	{
		// 프로젝타일 세팅
		ObjectProjecTile* SwitchProjec = mSkils[(int)eSkilType::Switch];
		SwitchProjec->SetScale(Vector2(3.0f, 3.0f));
		SwitchProjec->SetEvent(std::bind(&Samurai::SwitchProjecTile, this, std::placeholders::_1));
		SwitchProjec->SetTarget(this);
		SwitchProjec->SetReuse_Time(0.1f);
		SwitchProjec->SetEffectName(L"Sword_Switch_Eft");

		Collider* collider1 = SwitchProjec->GetComponent<Collider>();
		collider1->SetScale(Vector2(280.f, 70.f));
		Animator* animator1 = SwitchProjec->GetComponent<Animator>();
		animator1->CreatAnimations(SwitchProjec->GetEffectName(), L"..\\Resource\\Animation\\Effect\\SkeletonSword-Switch");
		animator1->SetAlpha(180);

		// 스킬 A 세팅
		ObjectProjecTile* SkilA = mSkils[(int)eSkilType::SkilA];
		SkilA->SetScale(Vector2(5.0f, 3.0f));
		SkilA->SetEvent(std::bind(&Samurai::SkilAProjecTile, this, std::placeholders::_1));
		SkilA->SetTarget(this);
		SkilA->SetReuse_Time(0.1f);
		SkilA->SetEffectName(L"_Sword_SkilA_Eft");
		SkilA->SetOffset(Vector2(50.f, 0.f));
		Collider* collider2 = SkilA->GetComponent<Collider>();
		collider2->SetScale(Vector2(200.f, 70.f));
		Animator* animator2 = SkilA->GetComponent<Animator>();
		animator2->CreatAnimations(L"L_Sword_SkilA_Eft", L"..\\Resource\\Animation\\Effect\\L_SkeletonSwordSlashEffect");
		animator2->CreatAnimations(L"R_Sword_SkilA_Eft", L"..\\Resource\\Animation\\Effect\\R_SkeletonSwordSlashEffect");
		animator2->SetAlpha(255);
		//스킬 B 세팅
		ObjectProjecTile* SkilB = mSkils[(int)eSkilType::SkilB];
		SkilB->SetScale(Vector2(5.0f, 3.0f));
		SkilB->SetEvent(std::bind(&Samurai::SkilBProjecTile, this, std::placeholders::_1));
		SkilB->SetTarget(this);
		SkilB->SetReuse_Time(1.0f);
		SkilB->SetEffectName(L"_Samurai_SkilB_Eft");
		SkilB->SetOffset(Vector2(200.f, 0.f));
		SkilB->SetNotMove(true);
		Collider* collider3 = SkilB->GetComponent<Collider>();
		collider3->SetScale(Vector2(300.f, 70.f));
		Animator* animator3 = SkilB->GetComponent<Animator>();
		animator3->CreatAnimations(L"L_Samurai_SkilB_Eft"
			, L"..\\Resource\\Animation\\Effect\\Samurai"
			, Vector2(0.f, 0.f), 0.07);

		animator3->CreatAnimations(L"R_Samurai_SkilB_Eft"
			, L"..\\Resource\\Animation\\Effect\\Samurai"
			, Vector2(0.f, 0.f), 0.07);
		animator3->SetAlpha(255);
	}

	void Samurai::OnAttackEffect(GameObject* other)
	{

	}
	void Samurai::SwitchProjecTile(GameObject* object)
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

	void Samurai::SkilAProjecTile(GameObject* object)
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

	void Samurai::SkilBProjecTile(GameObject* object)
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

	void Samurai::OnSkilB()
	{
		Rigidbody* rigidbody = GetComponent<Rigidbody>();
		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		if (mArrivalPos == Vector2::Zero)
		{
			mArrivalPos = GetPos();
			if (dirction)
				mArrivalPos.x += 300;
			else
				mArrivalPos.x -= 300;

			rigidbody->SetVelocity(Vector2::Zero);
		}

		if (dirction)
		{
			if (mArrivalPos.x > GetPos().x)
				rigidbody->AddForce(Vector2(4000.f, 0.0f));
		}
		else
		{
			if (mArrivalPos.x < GetPos().x)
				rigidbody->AddForce(Vector2(-4000.f, 0.0f));
		}


		if (GetComponent<Animator>()->isComplete())
			mArrivalPos = Vector2::Zero;
	}
}