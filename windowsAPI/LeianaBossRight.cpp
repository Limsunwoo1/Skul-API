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
#include "EventManager.h"

namespace sw
{
	LeianaBossRight::LeianaBossRight()
		: BossMonster()
		, mOwner(nullptr)
		, mbIn(false)
		, mbOut(false)
		, mHold(true)
		, mLScreenSpawnX(600.f)
		, mRScreenSpawnX(1800.f)
		, mScreenSpawnY(765.f)
		, mLScreenOutX(-20.f)
		, mRScreenOutX(2452.f)
		, mScreenOutY(503.f)
		, mDirVec(Vector2::Zero)
		, mSpeed(0)
	{
		SetDirPos(true);
	}

	LeianaBossRight::~LeianaBossRight()
	{
		delete mProjecTile;
		GameObject::~GameObject();
	}
	void LeianaBossRight::Tick()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		GameObject::Tick();

		Vector2 pos = GetPos();
		pos += mDirVec * Time::GetInstance()->DeltaTime() * mSpeed;
		mDirVec = Vector2::Zero;
		SetPos(pos);
	}

	void LeianaBossRight::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LeianaBossRight::Initialize()
	{
		// Init
		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();

		SetScale(4.5f, 4.5f);
		mScreenSpawnY = mScreenSpawnY - (GetComponent<Collider>()->GetScale().y * 0.5f);
		SetPos(mRScreenSpawnX, mScreenSpawnY);
	}

	void LeianaBossRight::InitializeAnimation()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"R_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\R", Vector2(-40.f, 20.f), 0.3f);
		animator->CreatAnimations(L"L_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\L", Vector2(40.f, 10.f), 0.3f);

		animator->CreatAnimations(L"MeteorReady", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MeteorReady", Vector2(-30.f, 0.f));
		animator->CreatAnimations(L"MeteorLanding", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MetoerLanding");

		animator->CreatAnimations(L"R_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\R");
		animator->CreatAnimations(L"L_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\L");

		animator->CreatAnimations(L"R_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\R", Vector2(0.f, 10.f));
		animator->CreatAnimations(L"L_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\L", Vector2(0.f, 10.f));

		animator->CreatAnimations(L"R_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\R", Vector2(0.f, 30.f));
		animator->CreatAnimations(L"L_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\L", Vector2(0.f, 30.f));

		animator->CreatAnimations(L"R_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\RigthBoss\\R");
		animator->CreatAnimations(L"L_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\RigthBoss\\L");

		animator->CreatAnimations(L"RDead", LEIANABOSS_GOLD_PATH + L"Dead\\R", Vector2(0.f, -50.f), 0.1f);

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
		mProjecTile = new ObjectProjecTile();

		mProjecTile->SetTarget(this);
		mProjecTile->SetReuse_Time(1.0f);

		Collider* collider = mProjecTile->GetComponent<Collider>();
		collider->SetScale(Vector2(30.f, 120.f));
	}

	void LeianaBossRight::Idle()
	{
		// 애니메이션랜더
		if (mPattonList[(int)eBossPatton::Idle] == false)
		{
			if (mDirPos)
				GetComponent<Animator>()->Play(L"L_Idle");
			else
				GetComponent<Animator>()->Play(L"R_Idle");


			mPattonList[(int)eBossPatton::Idle] = true;
		}

		mDelay = 2.0f;
		if (mDelta < mDelay)
			return;

		ScreenOut();
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
		if (mPattonState == ePattonState::READY)
			Patton2_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton2_Progress();
		if (mPattonState == ePattonState::END)
			Patton2_Stand_by(false);
	}

	void LeianaBossRight::Patton3()
	{
		if (mPattonState == ePattonState::READY)
			Patton3_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton3_Progress();
		if (mPattonState == ePattonState::END)
			Patton3_Stand_by(false);
	}

	void LeianaBossRight::Patton4()
	{

	}

	void LeianaBossRight::Patton1_Stand_by( bool type)
	{
		ScreenIn();
		if (!mbIn)
			return;

		mDelay = 2.0f;
		if (mDelta < mDelay)
			return;

		if (mHold)
			return;

		if (type)
		{
			if (IsDeath())
				SetDeath(false);

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
				if (mDirPos)
					GetComponent<Animator>()->Play(L"L_Idle");
				else
					GetComponent<Animator>()->Play(L"R_Idle");

				mProjecTile->SetDeath(true);
				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTile;

				EventManager::GetInstance()->EventPush(info);
			}

			if (GetComponent<Animator>()->isComplete())
			{
				mHold = true;
			}
		}
	}
	void LeianaBossRight::Patton1_Progress()
	{
		mSpeed = 800;
		mDirVec.y = mScreenSpawnY - GetPos().y;
		mDirVec.Normalize();

		if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorLanding")
		{
			GetComponent<Animator>()->Play(L"MeteorLanding");

			mProjecTile->SetDeath(false);
			mProjecTile->SetOffset(Vector2(0.f, 30.f));

			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTile;

			EventManager::GetInstance()->EventPush(info);
		}

		if (GetPos().y >= mScreenSpawnY)
			mPattonState = ePattonState::END;

	}
	void LeianaBossRight::Patton2_Stand_by(bool type)
	{
		ScreenIn();
		if (!mbIn)
			return;

		mDelay = 2.0f;
		if (mDelta < mDelay)
			return;

		if (type)
		{
			if (mPattonState != ePattonState::READY)
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_MeteorGroundReady"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_MeteorGroundReady")
			{
				if (GetComponent<Animator>()->isComplete())
				{
					mPattonState = ePattonState::LANDING;
				}
				return;
			}

			if (mDirPos)
				GetComponent<Animator>()->Play(L"L_MeteorGroundReady");
			else
				GetComponent<Animator>()->Play(L"R_MeteorGroundReady");
		}
		else
		{
			if (mPattonState != ePattonState::END)
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_MeteorGroundEnd"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_MeteorGroundEnd")
			{
				if (GetComponent<Animator>()->isComplete())
				{
					mHold = true;
				}
				return;
			}

			if (mDirPos)
				GetComponent<Animator>()->Play(L"L_MeteorGroundEnd");
			else
				GetComponent<Animator>()->Play(L"R_MeteorGroundEnd");

			mProjecTile->SetDeath(true);
			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTile;

			EventManager::GetInstance()->EventPush(info);
		}
	}
	void LeianaBossRight::Patton2_Progress()
	{
		if (mPattonState != ePattonState::LANDING)
			return;

		mSpeed = 1000;
		if (mDirPos)
		{
			mDirVec.x = 600.f - GetPos().x;
			mDirVec.Normalize();

			if (GetComponent<Animator>()->GetCurAnimationName() != L"L_MeteorGroundLanding")
			{
				GetComponent<Animator>()->Play(L"L_MeteorGroundLanding");

				mProjecTile->SetDeath(false);
				mProjecTile->SetOffset(Vector2(-40.f, 0.f));

				EventInfo info;
				info.Type = EventType::AddObejct;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTile;

				EventManager::GetInstance()->EventPush(info);
			}

			if (GetPos().x <= 600.f)
			{
				mPattonState = ePattonState::END;
			}
		}
		else
		{
			mDirVec.x = 1800.f - GetPos().x;
			mDirVec.Normalize();

			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_MeteorGroundLanding")
			{
				GetComponent<Animator>()->Play(L"R_MeteorGroundLanding");

				mProjecTile->SetDeath(false);
				mProjecTile->SetOffset(Vector2(40.f, 0.f));

				EventInfo info;
				info.Type = EventType::AddObejct;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTile;

				EventManager::GetInstance()->EventPush(info);
			}

			if (GetPos().x >= 1800.f)
			{
				mPattonState = ePattonState::END;
			}
		}
	}
	void LeianaBossRight::Patton3_Stand_by(bool type)
	{
		ScreenIn();
		if (!mbIn)
			return;

		mDelay = 3.0f;
		if (mDelta < mDelay)
			return;

		if (type)
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorReady")
			{
				GetComponent<Animator>()->Play(L"MeteorReady");
				SetDeath(true);
				SetPos(mPlayer->GetPos().x, mScreenSpawnY - 400.f);
				return;
			}

			if (IsDeath())
				SetDeath(false);

			if (GetComponent<Animator>()->isComplete())
				mPattonState = ePattonState::LANDING;
		}
		else
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_Idle"
				&& GetComponent<Animator>()->GetCurAnimationName() != L"L_Idle")
			{
				if (mDirPos)
					GetComponent<Animator>()->Play(L"L_Idle");
				else
					GetComponent<Animator>()->Play(L"R_Idle");

				mProjecTile->SetDeath(true);
				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTile;

				EventManager::GetInstance()->EventPush(info);
			}

			if (GetComponent<Animator>()->isComplete())
			{
				mHold = true;
			}
		}
	}
	void LeianaBossRight::Patton3_Progress()
	{
		mSpeed = 800;
		mDirVec.y = mScreenSpawnY - GetPos().y;
		mDirVec.Normalize();

		if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorLanding")
		{
			GetComponent<Animator>()->Play(L"MeteorLanding");

			mProjecTile->SetDeath(false);
			mProjecTile->SetOffset(Vector2(0.f, 30.f));

			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTile;

			EventManager::GetInstance()->EventPush(info);
		}

		if (GetPos().y >= mScreenSpawnY)
			mPattonState = ePattonState::END;
	}
	void LeianaBossRight::Patton4_Stand_by(bool type)
	{
		
	}
	void LeianaBossRight::Patton4_Progress()
	{
		
	}
	void LeianaBossRight::ScreenOut()
	{
		if (!mbOut)
		{
			Vector2 Pos = GetPos();
			mSpeed = 4000;

			if (mDirPos)
			{
				mDirVec = (Vector2(mRScreenOutX, mScreenOutY) - Pos).Normalize();
				GetComponent<Animator>()->Play(L"R_Dash");
				if (Pos.x >= mRScreenOutX && Pos.y <= mScreenOutY)
					mbOut = true;
			}
			else
			{
				mDirVec = (Vector2(mLScreenOutX, mScreenOutY) - Pos).Normalize();
				GetComponent<Animator>()->Play(L"L_Dash");
				if (Pos.x <= mLScreenOutX && Pos.y <= mScreenOutY)
					mbOut = true;
			}
		}
	}
	void LeianaBossRight::ScreenIn()
	{
		if (!mbIn)
		{
			Vector2 Pos = GetPos();
			mSpeed = 4000;

			if (mDirPos)
			{
				GetComponent<Animator>()->Play(L"L_Dash");
				mDirVec = (Vector2(mRScreenSpawnX, mScreenSpawnY) - Pos).Normalize();

				if (Pos.x <= mRScreenSpawnX && Pos.y >= mScreenSpawnY)
				{
					GetComponent<Animator>()->Play(L"L_Idle");

					mbIn = true;
					mDelta = 0.0f;
				}
			}
			else
			{
				GetComponent<Animator>()->Play(L"R_Dash");
				mDirVec = (Vector2(mLScreenSpawnX, mScreenSpawnY) - Pos).Normalize();

				if (Pos.x >= mLScreenSpawnX && Pos.y >= mScreenSpawnY)
				{
					GetComponent<Animator>()->Play(L"R_Idle");

					mbIn = true;
					mDelta = 0.0f;
				}
			}
		}
	}
	void LeianaBossRight::OffProjecTile()
	{
		EventInfo info;
		info.Type = EventType::DeleteObject;
		info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
		info.Parameter2 = mProjecTile;
		EventManager::GetInstance()->EventPush(info);

		mProjecTile->GetComponent<Animator>()->SetOnRender(false);
	}
}