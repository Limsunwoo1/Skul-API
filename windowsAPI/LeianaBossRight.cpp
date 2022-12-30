#include "LeianaBossRight.h"
#include "Time.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ObjectProjecTile.h"
#include "Path.h"
#include "Scene.h"
#include "MainPlayer.h"
#include "LeianaControler.h"

namespace sw
{
	LeianaBossRight::LeianaBossRight()
		: BossMonster()
		, mOwner(nullptr)
	{
	}

	LeianaBossRight::~LeianaBossRight()
	{
	}
	void LeianaBossRight::Tick()
	{
		LOG(STRING("틱 이전 포즈 %f", GetPos().y));
		GameObject::Tick();
		LOG(STRING("틱 이후 포즈 %f", GetPos().y));
		Branch();
	}

	void LeianaBossRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LeianaBossRight::Initialize()
	{
		SetPos(1800.f, 0.f);
		SetScale(4.5f, 4.5f);
		Rigidbody* rigd = AddComponent<Rigidbody>();
		rigd->SetOwner(this);

		// Init
		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();
	}

	void LeianaBossRight::InitializeAnimation()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"R_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\R");
		animator->CreatAnimations(L"L_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\L", Vector2(40.f, 10.f), 0.3f);

		animator->CreatAnimations(L"MeteorReady", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MeteorReady");
		animator->CreatAnimations(L"MeteorLanding", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MetoerLanding");

		animator->CreatAnimations(L"R_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\RigthBoss\\R");
		animator->CreatAnimations(L"L_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\RigthBoss\\L");

		animator->Play(L"L_Idle");
	}

	void LeianaBossRight::InitalizeCollider()
	{
		Collider* col = AddComponent<Collider>();
		col->SetOwner(this);
		col->SetPos(GetPos());
		col->SetScale(80.f, 120.f);
	}

	void LeianaBossRight::InitalizeProjecTile()
	{
		// Patton1

	}

	void LeianaBossRight::Idle()
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
	}
	void LeianaBossRight::Patton1()
	{
		if (mPattonState == ePattonState::READY)
			Patton1_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton1_Progress();
		if (mPattonState == ePattonState::END)
			Patton1_Stand_by(false);
	}

	void LeianaBossRight::Patton2()
	{

	}

	void LeianaBossRight::Patton3()
	{

	}

	void LeianaBossRight::Patton4()
	{

	}

	void LeianaBossRight::Patton1_Stand_by( bool type)
	{
		if (type)
		{
			if (IsDeath())
			{
				if (mPlayer)
				{
					Vector2 pPos = mPlayer->GetPos();
					SetPos(pPos.x, 400.f);
				}
				SetDeath(false);
				GetComponent<Rigidbody>()->SetGround(true);
			}

			if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorReady")
				GetComponent<Animator>()->Play(L"MeteorReady");

			if (GetComponent<Animator>()->isComplete())
				mPattonState = ePattonState::LANDING;
		}
		else
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_Idle"
			 && GetComponent<Animator>()->GetCurAnimationName() != L"L_Idle")
			{
				if (mDirction)
					GetComponent<Animator>()->Play(L"R_Idle");
				else
					GetComponent<Animator>()->Play(L"L_Idle");
			}

			if (GetComponent<Animator>()->isComplete())
			{
				mPattonState = ePattonState::NONE;
				mOwner->SetCurPatton(eBossPatton::Idle);
			}
		}
	}
	void LeianaBossRight::Patton1_Progress()
	{
		if (GetComponent<Rigidbody>()->GetGround())
			GetComponent<Rigidbody>()->SetGround(false);

		if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorLanding")
			GetComponent<Animator>()->Play(L"MeteorLanding");

		if (GetComponent<Animator>()->isComplete())
			mPattonState = ePattonState::END;

	}
	void LeianaBossRight::Patton2_Stand_by(bool type)
	{
		
	}
	void LeianaBossRight::Patton2_Progress()
	{
		
	}
	void LeianaBossRight::Patton3_Stand_by(bool type)
	{
		
	}
	void LeianaBossRight::Patton3_Progress()
	{
		
	}
	void LeianaBossRight::Patton4_Stand_by(bool type)
	{
		
	}
	void LeianaBossRight::Patton4_Progress()
	{
		
	}
}