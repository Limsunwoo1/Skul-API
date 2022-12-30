#include "LeianaBoss.h"
#include "Time.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ObjectProjecTile.h"
#include "Path.h"
#include "Scene.h"
#include "MainPlayer.h"
#include "LeianaControler.h"
#include "LeianaBossRight.h"
#include "CollisionManager.h"

namespace sw
{
	LeianaBoss::LeianaBoss()
		: BossMonster()
		, mOwner(nullptr)
		, mbIn(false)
		, mbOut(false)
	{
	}

	LeianaBoss::~LeianaBoss()
	{
	}

	void LeianaBoss::Tick()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		GameObject::Tick();
		Branch();
	}

	void LeianaBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LeianaBoss::Initialize()
	{
		SetPos(600.f, 0.f);
		SetScale(4.5f, 4.5f);
		Rigidbody* rigd = AddComponent<Rigidbody>();
		rigd->SetOwner(this);
		// Init
		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();
	}

	void LeianaBoss::InitializeAnimation()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"R_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\R", Vector2(-40.f,10.f ), 0.3f);
		animator->CreatAnimations(L"L_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\L");

		animator->CreatAnimations(L"R_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\R");
		animator->CreatAnimations(L"L_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\L");

		animator->CreatAnimations(L"R_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\R");
		animator->CreatAnimations(L"L_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\L");

		animator->CreatAnimations(L"R_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\R");
		animator->CreatAnimations(L"L_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\L");

		animator->CreatAnimations(L"R_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\LeftBoss\\R");
		animator->CreatAnimations(L"L_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\LeftBoss\\L");

		animator->Play(L"R_Idle");
	}

	void LeianaBoss::InitalizeCollider()
	{
		Collider* col = AddComponent<Collider>();
		col->SetOwner(this);
		col->SetPos(GetPos());
		col->SetScale(80.f, 120.f);
	}

	void LeianaBoss::InitalizeProjecTile()
	{
		// Patton1
		
	}

	void LeianaBoss::Idle()
	{
		// 애니메이션랜더
		if (mPattonList[(int)eBossPatton::Idle] == false)
		{
			if (mDirction)
				GetComponent<Animator>()->Play(L"R_Idle");
			else
				GetComponent<Animator>()->Play(L"L_Idle");


			mPattonList[(int)eBossPatton::Idle] = true;
		}

		if (GetComponent<Animator>()->GetCurAnimationName() == L"R_Idle"
			|| GetComponent<Animator>()->GetCurAnimationName() == L"L_Idle")
		{
			if (mDelta < 1.0f)
				return;
			
			if (mDirction)
				GetComponent<Animator>()->Play(L"L_Dash");
			else
				GetComponent<Animator>()->Play(L"R_Dash");

			mDelta = 0.0f;
			return;
		}

		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster, eColliderLayer::Ground, false);
		if (!mbIn)
		{
			if (mDelta < 1.0f)
			{
				CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster, eColliderLayer::Ground, false);
				Vector2 pos = GetPos();
				if (mDirction)
				{ 
					pos = pos - Time::GetInstance()->DeltaTime() * 400.f;
				}
				else
				{
					pos = pos + Time::GetInstance()->DeltaTime() * 400.f;
				}
				SetPos(pos);
			}
			else
			{
				if (mDirction)
					GetComponent<Animator>()->Play(L"R_Dash");
				else
					GetComponent<Animator>()->Play(L"L_Dash");

				mDelta = 0.0f;
				mbIn = true;
			}
			return;
		}
		else if (!mbOut)
		{
			if (mDelta < 1.0f)
			{
				CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster, eColliderLayer::Ground, false);
				Vector2 pos = GetPos();
				if (mDirction)
				{
					pos = pos + Time::GetInstance()->DeltaTime() * 400.f;

				}
				else
				{
					pos = pos - Time::GetInstance()->DeltaTime() * 400.f;
				}
				SetPos(pos);
			}

			return;
		}

		CollisionManager::GetInstance()->SetLayer(eColliderLayer::BossMonster, eColliderLayer::Ground);
	}
	void LeianaBoss::Patton1()
	{
		if (mPattonState == ePattonState::READY)
			Patton1_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton1_Progress();
		if (mPattonState == ePattonState::END)
			Patton1_Stand_by(false);
	}

	void LeianaBoss::Patton2()
	{

	}

	void LeianaBoss::Patton3()
	{

	}

	void LeianaBoss::Patton4()
	{

	}

	void LeianaBoss::Patton1_Stand_by(bool type)
	{
		if (type)
		{
			if (mPattonState != ePattonState::READY)
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_MeteorGroundReady"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_MeteorGroundReady")
			{
				if (GetComponent<Animator>()->isComplete())
					mPattonState = ePattonState::LANDING;

				return;
			}

			if (mDirction)
				GetComponent<Animator>()->Play(L"R_MeteorGroundReady");
			else
				GetComponent<Animator>()->Play(L"L_MeteorGroundReady");
		}
		else
		{
			if (mPattonState != ePattonState::END)
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_MeteorGroundEnd"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_MeteorGroundEnd")
			{
				if (GetComponent<Animator>()->isComplete())
					mPattonState = ePattonState::NONE;
				return;
			}

			if (mDirction)
				GetComponent<Animator>()->Play(L"R_MeteorGroundEnd");
			else
				GetComponent<Animator>()->Play(L"L_MeteorGroundEnd");
		}
	}
	void LeianaBoss::Patton1_Progress()
	{
		if (mPattonState != ePattonState::LANDING)
			return;

		if (mDirction)
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_MeteorGroundLanding")
				GetComponent<Animator>()->Play(L"R_MeteorGroundLanding");

			if (GetPos().x < 2100.f)
				GetComponent<Rigidbody>()->AddForce(1000.f, 0.f);
			else
				mPattonState = ePattonState::END;

			if (GetPos().x > 1800.f)
			{
				mOwner->GetRightLeiana()->SetDeath(true);
				mOwner->GetRightLeiana()->SetCurPattonState(ePattonState::READY);
			}
		}
		else
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"L_MeteorGroundLanding")
				GetComponent<Animator>()->Play(L"L_MeteorGroundLanding");

			if (GetPos().x > 300.f)
				GetComponent<Rigidbody>()->AddForce(-1000.f, 0.f); 
			else 
				mPattonState = ePattonState::END;

			if (GetPos().x < 600.f)
			{
				mOwner->GetRightLeiana()->SetDeath(true);
				mOwner->GetRightLeiana()->SetCurPattonState(ePattonState::READY);
			}
		}
	}
	void LeianaBoss::Patton2_Stand_by(bool type)
	{
	
	}
	void LeianaBoss::Patton2_Progress()
	{
		
	}
	void LeianaBoss::Patton3_Stand_by( bool type)
	{
		
	}
	void LeianaBoss::Patton3_Progress()
	{
		
	}
	void LeianaBoss::Patton4_Stand_by (bool type)
	{
		
	}
	void LeianaBoss::Patton4_Progress()
	{
		
	}
}