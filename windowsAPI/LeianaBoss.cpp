#include "LeianaBoss.h"
#include "Time.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "ObjectProjecTile.h"

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

		SetDelay(2.0f);
	}

	LeianaBoss::~LeianaBoss()
	{
	}
	void LeianaBoss::Tick()
	{
		GameObject::Tick();
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
		GameObject::Render(hdc);
	}

	void LeianaBoss::Initialize()
	{
		mLeftBoss = new  GameObject();
		Rigidbody* rgid1 = AddComponent<Rigidbody>();
		rgid1->SetOwner(mLeftBoss);

		mRightBoss = new GameObject();
		Rigidbody* rgid2 = AddComponent<Rigidbody>();
		rgid2->SetOwner(mRightBoss);

		InitializeAnimation();
		InitalizeCollider();
		InitalizeProjecTile();
	}

	void LeianaBoss::InitializeAnimation()
	{
		Animator* animator1 = AddComponent<Animator>();
		animator1->SetOwner(mLeftBoss);

		Animator* animator2 = AddComponent<Animator>();
		animator2->SetOwner(mRightBoss);
	}

	void LeianaBoss::InitalizeCollider()
	{
		Collider* collider1 = AddComponent<Collider>();
		collider1->SetOwner(mLeftBoss);
		collider1->SetScale(80.f, 80.f);

		Collider* collider2 = AddComponent<Collider>();
		collider2->SetOwner(mRightBoss);
		collider2->SetScale(80.f, 80.f);
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
			mLeftBoss->SetPos(0.0f,0.0f);
			mRightBoss->SetPos(1800.0f, 0.0f);

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
}