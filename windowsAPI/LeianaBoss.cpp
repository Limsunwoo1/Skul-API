#include "LeianaBoss.h"
#include "Time.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ObjectProjecTile.h"
#include "Path.h"
#include "Scene.h"

namespace sw
{
	LeianaBoss::LeianaBoss()
		: BossMonster()
		, mLeftBoss(nullptr)
		, mRightBoss(nullptr)
		, mDarkBoss(nullptr)
	{
		mCurPatton = eBossPatton::Idle;
		for (int i = (int)eBossPatton::Idle; i < (int)eBossPatton::End; ++i)
		{
			mPattonList.push_back(false);
		}
		Initialize();
		SetDelay(200.0f);
	}

	LeianaBoss::~LeianaBoss()
	{
	}
	void LeianaBoss::Tick()
	{
		mLeftBoss->Tick();
		mRightBoss->Tick();

		mDelta += Time::GetInstance()->DeltaTime();

		switch (mCurPatton)
		{
		case eBossPatton::Idle:
		{
			Idle();
		}
		break;
		case eBossPatton::Patton1:
		{
			Patton1();
		}
		break;
		case eBossPatton::Patton2:
		{
			Patton2();
		}
		break;
		case eBossPatton::Patton3:
		{
			Patton3();
		}
		break;
		case eBossPatton::Patton4:
		{
			Patton4();
		}
		break;
		case eBossPatton::End:
		{
			
		}
		break;

		}
	}

	void LeianaBoss::Render(HDC hdc)
	{
		mLeftBoss->Render(hdc);
		mRightBoss->Render(hdc);
	}

	void LeianaBoss::Initialize()
	{
		// 왼쪽 보스
		mLeftBoss = new  GameObject();
		mLeftBoss->SetPos(0.0f, 100.f);
		mLeftBoss->SetScale(3.5f, 3.5f);
		Rigidbody* rgid1 = new Rigidbody();
		mLeftBoss->AddComponent(rgid1);

		// 오른쪽 보스
		mRightBoss = new GameObject();
		mRightBoss->SetPos(1600.f, 100.f);
		mRightBoss->SetScale(3.5f, 3.5f);
		Rigidbody* rgid2 = new Rigidbody();
		mRightBoss->AddComponent(rgid2);

		// Init
		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();
	}

	void LeianaBoss::InitializeAnimation()
	{
		Animator* animator1 = new Animator();
		animator1->CreatAnimations(L"RIdle", LEIANABOSS_GOLD_PATH + L"Idle\\R", Vector2(-20.f, 10.f), 0.3f);
		mLeftBoss->AddComponent(animator1);

		Animator* animator2 = new Animator();
		animator2->CreatAnimations(L"LIdle", LEIANABOSS_GOLD_PATH + L"Idle\\L",Vector2(20.f, 10.f), 0.3f);
		mRightBoss->AddComponent(animator2);
	}

	void LeianaBoss::InitalizeCollider()
	{
		Collider* collider1 = new Collider();
		collider1->SetScale(80.f, 120.f);
		mLeftBoss->AddComponent(collider1);

		Collider* collider2 = new Collider();
		collider2->SetScale(80.f, 120.f);
		mRightBoss->AddComponent(collider2);
	}

	void LeianaBoss::InitalizeProjecTile()
	{
		// Patton1
		ObjectProjecTile* lpatton1 = new ObjectProjecTile();
		lpatton1->SetTarget(mLeftBoss);

		ObjectProjecTile* rpatton1 = new ObjectProjecTile();
		rpatton1->SetTarget(mRightBoss);

		// Patton2
		ObjectProjecTile* lpatton2 = new ObjectProjecTile();
		lpatton2->SetTarget(mLeftBoss);

		ObjectProjecTile* rpatton2 = new ObjectProjecTile();
		rpatton2->SetTarget(mRightBoss);

		// Patton3
		ObjectProjecTile* lpatton3 = new ObjectProjecTile();
		lpatton3->SetTarget(mLeftBoss);

		ObjectProjecTile* rpatton3 = new ObjectProjecTile();
		rpatton3->SetTarget(mRightBoss);

		// Patton4
		ObjectProjecTile* lpatton4 = new ObjectProjecTile();
		lpatton4->SetTarget(mLeftBoss);

		ObjectProjecTile* rpatton4 = new ObjectProjecTile();
		rpatton4->SetTarget(mRightBoss);
	}

	void LeianaBoss::Idle()
	{
		// 애니메이션랜더
		if (mPattonList[(int)eBossPatton::Idle] == false)
		{
			mLeftBoss->SetPos(300.f,600.0f);
			mLeftBoss->GetComponent<Animator>()->Play(L"RIdle",true);

			mRightBoss->SetPos(1800.0f, 600.0f);
			mRightBoss->GetComponent<Animator>()->Play(L"LIdle",true);
			mPattonList[(int)eBossPatton::Idle] = true;
		}
		// 랜덤값 으로 다음패턴세팅 하기
		if (mDelta > mDelay)
		{
			SetCurPatton(mNextPatton);
			mDelta = 0.0f;
			mNextPatton = eBossPatton::Idle;
			mPattonList[(int)eBossPatton::Idle] = false;
		}
	}
	void LeianaBoss::Patton1()
	{
		// 자매의 애니메이션 세팅
		//세팅후 두자매의 움직임구현
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
	void LeianaBoss::PushBoss(Scene* scen)
	{
		scen->AddGameObject(mLeftBoss, eColliderLayer::BossMonster);
		scen->AddGameObject(mRightBoss, eColliderLayer::BossMonster);
	}
}