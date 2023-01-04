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
#include "EventManager.h"
namespace sw
{
	LeianaBoss::LeianaBoss()
		: BossMonster()
		, mOwner(nullptr)
		, mbIn(false)
		, mbOut(false)
		, mHold(false)
		, mRushEnd(false)
		, mPatton6_ProjecTile_Ready(false)
		, mPatton6_ProjecTile_End(false)
		, mLScreenSpawnX(600.f)
		, mRScreenSpawnX(1800.f)
		, mScreenSpawnY(765.f)
		, mLScreenOutX(-20.f)
		, mRScreenOutX(2452.f)
		, mScreenOutY(503.f)
		, mRisignPrerceDelay(0.f)
		, mDirVec(Vector2::Zero)
		, mSpeed(0)
		, mPatton5_Num(0)
		, mPatton5_TargetPos(0.f,0.f)
	{
		SetDirPos(false);
	}

	LeianaBoss::~LeianaBoss()
	{
		for (GameObject* object : mProjecTiles)
		{
			if (object == nullptr)
				continue;

			delete object;
		}
		mProjecTiles.clear();

		delete mProjecTile;
	}

	void LeianaBoss::Tick()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		mDirVec = Vector2::Zero;

		GameObject::Tick();
		Branch();
		
		Vector2 pos = GetPos();
		pos += mDirVec * Time::GetInstance()->DeltaTime() * mSpeed;
		SetPos(pos);
	}

	void LeianaBoss::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void LeianaBoss::Initialize()
	{
		// Init
		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();

		SetScale(4.5f, 4.5f);
		mScreenSpawnY = mScreenSpawnY - (GetComponent<Collider>()->GetScale().y * 0.5f);
		SetPos(mLScreenSpawnX, mScreenSpawnY);

		mPatton5_Entry.push_back(L"_RushA");
		mPatton5_Entry.push_back(L"_RushB");
		mPatton5_Entry.push_back(L"_RushC");
	}

	void LeianaBoss::InitializeAnimation()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"R_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\R", Vector2(-40.f,20.f ), 0.3f);
		animator->CreatAnimations(L"L_Idle", LEIANABOSS_GOLD_PATH + L"Idle\\L", Vector2(40.f,20.f), 0.3f);

		animator->CreatAnimations(L"R_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\LeftBoss\\R");
		animator->CreatAnimations(L"L_Dash", LEIANABOSS_GOLD_PATH + L"Dash\\LeftBoss\\L");

		animator->CreatAnimations(L"MeteorReady", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MeteorReady", Vector2(-30.f, 0.f));
		animator->CreatAnimations(L"MeteorLanding", LEIANABOSS_GOLD_PATH + L"combe\\Meteor\\MetoerLanding");

		animator->CreatAnimations(L"L_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\L");
		animator->CreatAnimations(L"R_MeteorGroundReady", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Ready.01\\R");


		animator->CreatAnimations(L"R_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\R", Vector2(0.f, 10.f));
		animator->CreatAnimations(L"L_MeteorGroundLanding", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_Landing\\L", Vector2(0.f, 10.f));

		animator->CreatAnimations(L"R_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\R", Vector2(0.f, 30.f));
		animator->CreatAnimations(L"L_MeteorGroundEnd", LEIANABOSS_GOLD_PATH + L"combe\\MeteorGround\\Meteor_Ground_End\\L", Vector2(0.f, 30.f));

		animator->CreatAnimations(L"R_RushReady", LEIANABOSS_GOLD_PATH + L"Rush\\R\\Ready");
		animator->CreatAnimations(L"L_RushReady", LEIANABOSS_GOLD_PATH + L"Rush\\L\\Ready");

		animator->CreatAnimations(L"R_RushA", LEIANABOSS_GOLD_PATH + L"Rush\\R\\RushA");
		animator->CreatAnimations(L"L_RushA", LEIANABOSS_GOLD_PATH + L"Rush\\L\\RushA");

		animator->CreatAnimations(L"R_RushB", LEIANABOSS_GOLD_PATH + L"Rush\\R\\RushB");
		animator->CreatAnimations(L"L_RushB", LEIANABOSS_GOLD_PATH + L"Rush\\L\\RushB");

		animator->CreatAnimations(L"R_RushC", LEIANABOSS_GOLD_PATH + L"Rush\\R\\RushC");
		animator->CreatAnimations(L"L_RushC", LEIANABOSS_GOLD_PATH + L"Rush\\L\\RushC");

		animator->CreatAnimations(L"R_RushEnd", LEIANABOSS_GOLD_PATH + L"Rush\\R\\End", Vector2(0.f, 30.f));
		animator->CreatAnimations(L"L_RushEnd", LEIANABOSS_GOLD_PATH + L"Rush\\L\\End", Vector2(0.f, 30.f));

		animator->CreatAnimations(L"R_RisignePrerceReady", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\Ready\\R",Vector2(40.f, 70.f), 0.2f);
		animator->CreatAnimations(L"L_RisignePrerceReady", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\Ready\\L", Vector2(-40.f, 70.f), 0.2f);

		animator->CreatAnimations(L"R_RisignePrerceLanding", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\Landing\\R", Vector2(40.f, 70.f), 0.2f);
		animator->CreatAnimations(L"L_RisignePrerceLanding", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\Landing\\L", Vector2(-40.f, 70.f), 0.2f);

		animator->CreatAnimations(L"R_RisignePrerceEnd", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\End\\R", Vector2(40.f, 70.f), 0.2f);
		animator->CreatAnimations(L"L_RisignePrerceEnd", LEIANABOSS_GOLD_PATH + L"RisignPrerce\\End\\L", Vector2(-40.f, 70.f), 0.2f);

		animator->CreatAnimations(L"R_RisignePrerceAttack", LEIANABOSS_GOLD_PATH + L"DimensionPierce_Attack\\R", Vector2(0.f, 40.f), 0.2f);
		animator->CreatAnimations(L"L_RisignePrerceAtaack", LEIANABOSS_GOLD_PATH + L"DimensionPierce_Attack\\L", Vector2(0.f, 40.f), 0.2f);

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
		for (int i = 0; i < 10; ++i)
		{
			ObjectProjecTile* projectile = new ObjectProjecTile();

			projectile->SetTarget(this);
			projectile->SetReuse_Time(1.0f);
			projectile->SetEffectName(L"2CHBoss_Patton6");
			projectile->GetComponent<Animator>()->
				CreatAnimations(L"RisingPiereceEft_Ready", 
					L"..\\Resource\\Animation\\2CH_Boss\\Gold\\RisingPierceEffect\\Ready");

			projectile->GetComponent<Animator>()->
				CreatAnimations(L"RisingPiereceEft_Landing",
					L"..\\Resource\\Animation\\2CH_Boss\\Gold\\RisingPierceEffect\\RisingPierce");

			projectile->GetComponent<Animator>()->
				CreatAnimations(L"R_DimensionAttackEft", LEIANABOSS_GOLD_PATH + L"DimensionPierceAttackEft\\R");

			projectile->GetComponent<Animator>()->
				CreatAnimations(L"L_DimensionAttackEft", LEIANABOSS_GOLD_PATH + L"DimensionPierceAttackEft\\L");

			Collider* collider = projectile->GetComponent<Collider>();
			collider->SetScale(Vector2(30.f, 120.f));

			mProjecTiles.push_back(projectile);
		}

		mProjecTile = new ObjectProjecTile();
		mProjecTile->SetTarget(this);
		mProjecTile->SetReuse_Time(1.0f);

		Collider* collider = mProjecTile->GetComponent<Collider>();
		collider->SetScale(Vector2(30.f, 120.f));
	}

	void LeianaBoss::Idle()
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
		if (mPattonState == ePattonState::READY)
			Patton2_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton2_Progress();
		if (mPattonState == ePattonState::END)
			Patton2_Stand_by(false);
	}

	void LeianaBoss::Patton3()
	{
		if (mPattonState == ePattonState::READY)
			Patton3_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton3_Progress();
		if (mPattonState == ePattonState::END)
			Patton3_Stand_by(false);
	}

	void LeianaBoss::Patton4()
	{

	}

	void LeianaBoss::Patton5()
	{
		if (mPattonState == ePattonState::READY)
			Patton5_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton5_Progress();
		if (mPattonState == ePattonState::END)
			Patton5_Stand_by(false);
	}

	void LeianaBoss::Patton6()
	{
		if (mPattonState == ePattonState::READY)
			Patton6_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton6_Progress();
		if (mPattonState == ePattonState::END)
			Patton6_Stand_by(false);
	}

	void LeianaBoss::Patton7()
	{
		if (mPattonState == ePattonState::READY)
			Patton7_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton7_Progress();
		if (mPattonState == ePattonState::END)
			Patton7_Stand_by(false);
	}

	void LeianaBoss::Patton8()
	{
		if (mPattonState == ePattonState::READY)
			Patton8_Stand_by();
		if (mPattonState == ePattonState::LANDING)
			Patton8_Progress();
		if (mPattonState == ePattonState::END)
			Patton8_Stand_by(false);
	}

	void LeianaBoss::Patton1_Stand_by(bool type)
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

			if (PattonEnd())
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
	void LeianaBoss::Patton1_Progress()
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

			if (GetPos().x < 800.f)
			{
				if (mOwner->GetRightLeiana()->GetHold())
				{
					mOwner->GetRightLeiana()->SetDeath(true);
					mOwner->GetRightLeiana()->SetHold(false);
					mOwner->GetRightLeiana()->SetPos(mPlayer->GetPos().x, mScreenSpawnY - 400.f);
				}
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

			if (GetPos().x > 1600.f)
			{
				if (mOwner->GetRightLeiana()->GetHold())
				{
					mOwner->GetRightLeiana()->SetDeath(true);
					mOwner->GetRightLeiana()->SetHold(false);
					mOwner->GetRightLeiana()->SetPos(mPlayer->GetPos().x, mScreenSpawnY - 400.f);
				}
			}
		}
	}
	void LeianaBoss::Patton2_Stand_by(bool type)
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

			if (PattonEnd())
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
	void LeianaBoss::Patton2_Progress()
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

				int num = GetProJecTileNum();

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
	void LeianaBoss::Patton3_Stand_by( bool type)
	{
		ScreenIn();
		if (!mbIn)
			return;

		mDelay = 2.0f;
		if (mDelta < mDelay)
			return;

		if (type)
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorReady")
			{
				GetComponent<Animator>()->Play(L"MeteorReady");
				SetDeath(true);
				SetPos(mPlayer->GetPos().x, mScreenSpawnY - 400.f);
				ProJecTileNumSetting();
				return;
			}

			if (IsDeath())
				SetDeath(false);

			if (GetComponent<Animator>()->isComplete())
				mPattonState = ePattonState::LANDING;
		}
		else
		{
			if (PattonEnd())
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_Idle"
				&& GetComponent<Animator>()->GetCurAnimationName() != L"L_Idle")
			{
				if (mDirPos)
					GetComponent<Animator>()->Play(L"L_Idle");
				else
					GetComponent<Animator>()->Play(L"R_Idle");

				int num = GetProJecTileNum();
				mProjecTiles[num]->SetDeath(true);

				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTiles[num];

				EventManager::GetInstance()->EventPush(info);

				SetProJecTileNum(0);
			}

			if (GetComponent<Animator>()->isComplete())
			{
				mHold = true;
			}
		}
	}
	void LeianaBoss::Patton3_Progress()
	{
		mSpeed = 800;
		mDirVec.y = mScreenSpawnY - GetPos().y;
		mDirVec.Normalize();

		if (GetComponent<Animator>()->GetCurAnimationName() != L"MeteorLanding")
		{
			GetComponent<Animator>()->Play(L"MeteorLanding");

			int num = GetProJecTileNum();

			mProjecTiles[num]->SetDeath(false);
			mProjecTiles[num]->SetOffset(Vector2(0.f, 30.f));

			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTiles[num];

			EventManager::GetInstance()->EventPush(info);
		}

		if (GetPos().y >= mScreenSpawnY)
			mPattonState = ePattonState::END;
	}
	void LeianaBoss::Patton4_Stand_by (bool type)
	{
		
	}
	void LeianaBoss::Patton4_Progress()
	{
		
	}
	void LeianaBoss::Patton5_Stand_by(bool type)
	{
		ScreenIn();
		if (!mbIn)
			return;
		if (mPatton5_Num >= mPatton5_Entry.size())
		{
			mPatton5_Num = 0;
			mPattonState = ePattonState::END;
			type = false;
		}

		mDelay = 0.5f;
		if (mDelta < mDelay)
			return;

		if (type)
		{
			if (mPattonState != ePattonState::READY)
				return;

			mSpeed = 1000;
			if (mPatton5_TargetPos == Vector2::Zero)
			{
				mPatton5_TargetPos = mPlayer->GetPos();
				mPatton5_TargetPos.y = mScreenSpawnY;
				if (GetPos().x < mPatton5_TargetPos.x)
					mDirPos = false;
				else
					mDirPos = true;
			}

			mDirVec = (mPatton5_TargetPos - GetPos()).Normalize();

			if (mDirPos)
			{
				if (GetPos().x <= mPatton5_TargetPos.x)
					mPattonState = ePattonState::LANDING;
			}
			else
			{
				if (GetPos().x >= mPatton5_TargetPos.x)
					mPattonState = ePattonState::LANDING;
			}

			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_RushReady"
				&& GetComponent<Animator>()->GetCurAnimationName() != L"L_RushReady")
			{
				if (mDirPos)
					GetComponent<Animator>()->Play(L"R_RushReady");
				else
					GetComponent<Animator>()->Play(L"L_RushReady");
			}
		}
		else
		{
			if (mPattonState != ePattonState::END)
				return;

			mPattonState = ePattonState::NONE;
			mOwner->GetRightLeiana()->SetCurPattonState(ePattonState::NONE);
			mOwner->SetPatternProgress(false);
			mOwner->SetCurPatton(eBossPatton::Idle);
			mPattonList[(int)eBossPatton::Idle] = false;

			if (GetPos().x > mPlayer->GetPos().x)
				mDirPos = true;
			else
				mDirPos = false;
		}
	}
	void LeianaBoss::Patton5_Progress()
	{
		if (mPattonState != ePattonState::LANDING)
			return;

		if (!mRushEnd)
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"L" + mPatton5_Entry[mPatton5_Num]
				&& GetComponent<Animator>()->GetCurAnimationName() != L"R" + mPatton5_Entry[mPatton5_Num])
			{
				Vector2 offset = Vector2::Zero;

				if (mDirPos)
				{
					GetComponent<Animator>()->Play(L"R" + mPatton5_Entry[mPatton5_Num]);
					offset.x = -40.f;
				}
				else
				{
					GetComponent<Animator>()->Play(L"L" + mPatton5_Entry[mPatton5_Num]);
					offset.x = 40.f;
				}

				mProjecTile->GetComponent<Collider>()->SetScale(Vector2(80.f, 80.f));
				mProjecTile->SetDeath(false);
				mProjecTile->SetOffset(offset);

				EventInfo info;
				info.Type = EventType::AddObejct;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTile;

				EventManager::GetInstance()->EventPush(info);
			}
		}
		
		
		if (GetComponent<Animator>()->GetCurAnimationName() == L"L" + mPatton5_Entry[mPatton5_Num]
			|| GetComponent<Animator>()->GetCurAnimationName() == L"R" + mPatton5_Entry[mPatton5_Num])
		{
			if (GetComponent<Animator>()->isComplete())
			{
				if (!mRushEnd)
				{
					if (mDirPos)
						GetComponent<Animator>()->Play(L"R_RushEnd");
					else
						GetComponent<Animator>()->Play(L"L_RushEnd");

					mProjecTile->GetComponent<Collider>()->SetScale(Vector2(30.f, 120.f));
					mProjecTile->SetDeath(true);

					EventInfo info;
					info.Type = EventType::DeleteObject;
					info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
					info.Parameter2 = mProjecTile;

					EventManager::GetInstance()->EventPush(info);

					mRushEnd = true;
				}
			}
		}

		if (GetComponent<Animator>()->GetCurAnimationName() == L"R_RushEnd"
			|| GetComponent<Animator>()->GetCurAnimationName() == L"L_RushEnd")
		{
			if (GetComponent<Animator>()->isComplete())
			{
				++mPatton5_Num;
				mPattonState = ePattonState::READY;
				mPatton5_TargetPos = Vector2::Zero;
				mRushEnd = false;
				mDelta = 0.0f;
			}
		}
	}
	void LeianaBoss::Patton6_Stand_by(bool type)
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

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_RisignePrerceReady"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_RisignePrerceReady")
			{
				if (GetComponent<Animator>()->isComplete())
				{
					mPattonState = ePattonState::LANDING;
					mRisignPrerceDelay = 0.0f;
				}
				return;
			}

			if (GetPos().x < mPlayer->GetPos().x)
				mDirPos = false;
			else
				mDirPos = true;

			if (mDirPos)
				GetComponent<Animator>()->Play(L"R_RisignePrerceReady");
			else
				GetComponent<Animator>()->Play(L"L_RisignePrerceReady");
		}
		else
		{
			if (mPattonState != ePattonState::END)
				return;

			if (GetComponent<Animator>()->GetCurAnimationName() == L"R_RisignePrerceEnd"
				|| GetComponent<Animator>()->GetCurAnimationName() == L"L_RisignePrerceEnd")
			{
				if (GetComponent<Animator>()->isComplete())
				{
					mPattonState = ePattonState::NONE;
					mHold = false;
					mbIn = false;

					mOwner->SetCurPatton(eBossPatton::Idle);
					//mOwner->SetPatternProgress(false);
				}
				return;
			}

			if (mDirPos)
				GetComponent<Animator>()->Play(L"R_RisignePrerceEnd");
			else
				GetComponent<Animator>()->Play(L"L_RisignePrerceEnd");
		}
	}
	void LeianaBoss::Patton6_Progress()
	{
		if (mPattonState != ePattonState::LANDING)
			return;

		if (!mPatton6_ProjecTile_Ready)
		{
			if (mDirPos)
			{
				if (GetComponent<Animator>()->GetCurAnimationName() != L"R_RisignePrerceLanding")
					GetComponent<Animator>()->Play(L"R_RisignePrerceLanding");
			}
			else
			{
				if (GetComponent<Animator>()->GetCurAnimationName() != L"L_RisignePrerceLanding")
					GetComponent<Animator>()->Play(L"L_RisignePrerceLanding");
			}
			Patton6_ProjecTileReady();
		}

		Patton6_ProjecTileEnd();

		if (mPatton6_ProjecTile_End)
		{
			mPatton6_ProjecTile_Ready = false;
			mPatton6_ProjecTile_End = false;
			return;
		}

		Patton6_ProjecTileLading();
	}
	void LeianaBoss::Patton7_Stand_by(bool type)
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

			if (GetPos().x < mPlayer->GetPos().x)
				mDirPos = false;
			else
				mDirPos = true;

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
					mPattonState = ePattonState::NONE;
					mHold = false;
					mbIn = false;

					mOwner->SetCurPatton(eBossPatton::Idle);
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
	void LeianaBoss::Patton7_Progress()
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
	void LeianaBoss::Patton8_Stand_by(bool type)
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

			if (GetComponent<Animator>()->isComplete())
			{
				if (GetPos().x < mPlayer->GetPos().x)
					mDirPos = false;
				else
					mDirPos = true;

				mPattonState = ePattonState::LANDING;
			}
		}
		else
		{
			if (mPattonState != ePattonState::END)
				return;

			CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::BossMonster_ProjecTile);

			if (mProjecTiles[9]->GetComponent<Animator>()->isComplete())
			{
				mPattonState = ePattonState::NONE;
				mHold = false;
				mbIn = false;

				mOwner->SetCurPatton(eBossPatton::Idle);

				mProjecTiles[9]->SetDeath(true);
				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTiles[9];

				EventManager::GetInstance()->EventPush(info);
			}
		}
	}
	void LeianaBoss::Patton8_Progress()
	{
		if (mPattonState != ePattonState::LANDING)
			return;

		if (GetComponent<Animator>()->GetCurAnimationName() == L"R_RisignePrerceAttack"
			|| GetComponent<Animator>()->GetCurAnimationName() == L"L_RisignePrerceAtaack")
		{
			if (GetComponent<Animator>()->isComplete())
			{
				mPattonState = ePattonState::END;
				Vector2 offset = Vector2::Zero;
				offset = mPlayer->GetPos() - GetPos();

				if (mDirPos)
					mProjecTiles[9]->GetComponent<Animator>()->Play(L"R_DimensionAttackEft");
				else
					mProjecTiles[9]->GetComponent<Animator>()->Play(L"L_DimensionAttackEft");

				mProjecTiles[9]->SetDeath(false);
				mProjecTiles[9]->SetScale(Vector2(3.0f, 4.0f));
				mProjecTiles[9]->SetOffset(offset);

				EventInfo info;
				info.Type = EventType::AddObejct;
				info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
				info.Parameter2 = mProjecTiles[9];

				EventManager::GetInstance()->EventPush(info);

				CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::BossMonster_ProjecTile, false);
				return;
			}
		}

		if (mDirPos)
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"R_RisignePrerceAttack")
				GetComponent<Animator>()->Play(L"R_RisignePrerceAttack");
		}
		else
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"L_RisignePrerceAtaack")
				GetComponent<Animator>()->Play(L"L_RisignePrerceAtaack");
		}
	}

	void LeianaBoss::ScreenOut()
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
	void LeianaBoss::ScreenIn()
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
	bool LeianaBoss::PattonEnd()
	{
		if (mHold && mOwner->GetRightLeiana()->GetHold())
		{
			mPattonState = ePattonState::NONE;
			mHold = false;
			mbIn = false;

			mOwner->GetRightLeiana()->SetCurPattonState(ePattonState::NONE);
			mOwner->GetRightLeiana()->SetHold(true);
			mOwner->GetRightLeiana()->SetScreenIn(false);

			mOwner->SetCurPatton(eBossPatton::Idle);
			mOwner->SetPatternProgress(false);
			return true;
		}
		
		return false;
	}
	void LeianaBoss::ProJecTileNumSetting()
	{
		for (int i = 0; i < mProjecTiles.size(); ++i)
		{
			if (mProjecTiles[i]->IsDeath())
			{
				SetProJecTileNum(i);
			}
		}
	}
	void LeianaBoss::Patton6_ProjecTileReady()
	{
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::BossMonster_ProjecTile, false);
		int doubleCount = 0;
		float offsetPos = 60.f;
		float offsetDelta = 0.05f;

		for (int i = 0; i < mProjecTiles.size(); i++)
		{
			if (doubleCount >= 2)
			{
				offsetDelta += 0.05f;
				offsetPos += 60.f;

				doubleCount = 0;
			}

			if (doubleCount < 1)
				mProjecTiles[i]->SetOffset(Vector2(-1 * fabs(offsetPos), -30.f));
			else
				mProjecTiles[i]->SetOffset(Vector2(fabs(offsetPos), -30.f));

			mProjecTiles[i]->SetDeath(false);
			mProjecTiles[i]->SetScale(Vector2(2.0f, 3.0f));
			mProjecTiles[i]->SetStartOffset(offsetDelta);
			mProjecTiles[i]->GetComponent<Animator>()->Play(L"RisingPiereceEft_Ready");

			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTiles[i];

			EventManager::GetInstance()->EventPush(info);

			++doubleCount;
		}
		mPatton6_ProjecTile_Ready = true;
	}
	void LeianaBoss::Patton6_ProjecTileLading()
	{
		for (int i = 0; i < mProjecTiles.size(); ++i)
		{
			Animator* animator = mProjecTiles[i]->GetComponent<Animator>();
			if (!animator->isComplete())
				return;
			else
				mProjecTiles[i]->SetDeath(true);
		}

		int doubleCount = 0;
		float offsetdelta = 0.05f;
		for (int i = 0; i < mProjecTiles.size(); ++i)
		{
			mProjecTiles[i]->SetDeath(false);
			mProjecTiles[i]->GetComponent<Animator>()->Play(L"RisingPiereceEft_Landing");

			if (doubleCount >= 2)
			{
				offsetdelta += 0.05f;
				doubleCount = 0;
			}

			mProjecTiles[i]->SetStartOffset(offsetdelta);
			++doubleCount;
		}
		CollisionManager::GetInstance()->SetLayer(eColliderLayer::Player, eColliderLayer::BossMonster_ProjecTile);
	}
	void LeianaBoss::Patton6_ProjecTileEnd()
	{
		for (int i = 0; i < mProjecTiles.size(); ++i)
		{
			Animator* animator = mProjecTiles[i]->GetComponent<Animator>();
			if (!animator->isComplete() || animator->GetCurAnimationName() != L"RisingPiereceEft_Landing")
				return;
		}

		for (int i = 0; i < mProjecTiles.size(); ++i)
		{
			mProjecTiles[i]->SetDeath(true);

			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::BossMonster_ProjecTile);
			info.Parameter2 = mProjecTiles[i];

			EventManager::GetInstance()->EventPush(info);
		}

		mPatton6_ProjecTile_End = true;
		mPattonState = ePattonState::END;
	}
}