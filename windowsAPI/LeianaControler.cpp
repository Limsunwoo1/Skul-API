#include "LeianaControler.h"
#include "LeianaBoss.h"
#include "LeianaBossRight.h"
#include "Scene.h"
#include "Time.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Rigidbody.h"

#include <iostream>
#include <random>


std::random_device random1;
std::mt19937 gen1(random1());
std::uniform_int_distribution<int> CombePatton(1, 3);
std::uniform_int_distribution<int> SoloPatton(5, 8);

namespace sw
{
	LeianaControler::LeianaControler()
		: mLeft (nullptr)
		, mRight(nullptr)
		, mPlayer(nullptr)
		, mDelta(0.0f)
		, mDelay(3.0f)
		, mPatternProgress(false)
		, mCombeMode(true)
		, mDarkMode(false)
		, mPattonCount(0.f)
	{
		SetHp(90);
		SetPower(5);

		Initialize();
		mCurPatton = eBossPatton::Idle;
	}
	LeianaControler::~LeianaControler()
	{
	}
	void LeianaControler::Tick()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		Brunch();
	}
	void LeianaControler::Initialize()
	{
		mLeft = new LeianaBoss();
		mLeft->SetOwer(this);
		mLeft->Initialize();

		mRight = new LeianaBossRight();
		mRight->SetOwer(this);
		mRight->Initialize();
	}
	void LeianaControler::SetPlayer(MainPlayer* player)
	{
		mPlayer = player;
		mLeft->SetPlayer(player);
		mRight->SetPlayer(player);
	}
	void LeianaControler::SetCurPatton(eBossPatton type)
	{
		mCurPatton = type;
		mLeft->SetCurPatton(mCurPatton);
		mRight->SetCurPatton(mCurPatton);
	}
	void LeianaControler::Brunch()
	{
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
		case eBossPatton::Patton5:
		{
			Patton5();
		}
		break;
		case eBossPatton::Patton6:
		{
			Patton6();
		}
		break;
		case eBossPatton::Patton7:
		{
			Patton7();
		}
		break;
		case eBossPatton::Patton8:
		{
			Patton8();
		}
		break;
		case eBossPatton::Patton9:
		{
			Patton9();
		}
		case eBossPatton::Patton10:
		{
			Patton10();
		}
		break;
		}
	}
	void LeianaControler::Idle()
	{
		if (!mPatternProgress)
		{
			ReSetDirPos();
			mPatternProgress = true;
		}

		mLeft->Idle();
		mRight->Idle();

		if (mDelta < mDelay)
			return;

		if (mLeft->GetScreenOut() && mRight->GetScreenOut())
		{
			mLeft->SetScreenOut(false);
			mRight->SetScreenOut(false);

			if (mCombeMode)
			{
				mLeft->SetScreenIn(false);
				mRight->SetScreenIn(false);

				SetCurPatton((eBossPatton)CombePatton(gen1));
				mLeft->SetCurPattonState(ePattonState::READY);
				mRight->SetCurPattonState(ePattonState::READY);
				mPattonCount += 1.0f;
			}

			if (!mCombeMode)
			{
				mLeft->SetScreenOut(true);
				SetCurPatton((eBossPatton)SoloPatton(gen1));
				mLeft->SetCurPattonState(ePattonState::READY);

				mPattonCount += 0.5f;
				mDelta = 0.0f;
			}
		}

		if (mPattonCount >= 3.0f)
		{
			mPattonCount = 0.0f;
			if (mCombeMode)
			{
				mCombeMode = false;
			}
			else
			{
				mCombeMode = true;

				mLeft->SetScreenIn(false);
				mRight->SetScreenIn(false);

				mLeft->SetScreenOut(false);
				mRight->SetScreenOut(false);

				mLeft->SetDelta(0.0f);
				mRight->SetDelta(0.0f);

				mPatternProgress = false;
			}
		}
	}
	void LeianaControler::Patton1()
	{
		mLeft->Patton1();
		mRight->Patton1();
	}
	void LeianaControler::Patton2()
	{
		mLeft->Patton2();
		mRight->Patton2();
	}
	void LeianaControler::Patton3()
	{
		mLeft->Patton3();
		mRight->Patton3();
	}
	void LeianaControler::Patton4()
	{
		mLeft->Patton4();
		mRight->Patton4();
	}
	void LeianaControler::Patton5()
	{
		mLeft->Patton5();
		mRight->Patton5();
	}
	void LeianaControler::Patton6()
	{
		mLeft->Patton6();
		mRight->Patton6();
	}
	void LeianaControler::Patton7()
	{
		mLeft->Patton7();
		mRight->Patton7();
	}
	void LeianaControler::Patton8()
	{
		mLeft->Patton8();
		mRight->Patton8();
	}
	void LeianaControler::Patton9()
	{
		mLeft->Patton9();
		mRight->Patton9();
	}
	void LeianaControler::Patton10()
	{
		mLeft->Patton10();
		mRight->Patton10();
	}
	
	void LeianaControler::ReSetDirPos()
	{
		if (!mLeft)
			return;
		if (!mRight)
			return;

		if (mLeft->GetPos().x < mRight->GetPos().x)
		{
			mLeft->SetDirPos(false);
			mRight->SetDirPos(true);
		}
		else
		{
			mLeft->SetDirPos(true);
			mRight->SetDirPos(false);
		}
	}

	void LeianaControler::PushBoss(Scene* scene)
	{
		scene->AddGameObject(mLeft, eColliderLayer::BossMonster);
		scene->AddGameObject(mRight, eColliderLayer::BossMonster);
	}
}