#include "LeianaControler.h"
#include "LeianaBoss.h"
#include "LeianaBossRight.h"
#include "Scene.h"
#include "Time.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Rigidbody.h"

namespace sw
{
	LeianaControler::LeianaControler()
		: mLeft (nullptr)
		, mRight(nullptr)
		, mPlayer(nullptr)
		, mDelta(0.0f)
		, mDelay(3.0f)
		, mPatternProgress(false)
		, mPattonStarte(false)
		, mPattonEnd(false)
	{
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
		mRight->SetDirction(false);
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
		break;
		}
	}
	void LeianaControler::Idle()
	{
		mLeft->Idle();
		mRight->Idle();

		if (mDelta < mDelay)
			return;

		// 랜덤으로 다음패턴 설정 하기
		// SetNextPatton
		/*mNextPatton = eBossPatton::Patton1;
		mDelta = 0.0f;
		if (mNextPatton == eBossPatton::Patton1)
		{
			if (mLeft->GetPos().x < mPlayer->GetPos().x)
			{
				mLeft->SetDirction(true);
				mLeft->SetPos(600.f,mLeft->GetPos().y);
				mRight->SetPos(1900.f, mRight->GetPos().y);
			}
			else
			{
				mLeft->SetDirction(false);
				mLeft->SetPos(1900.f, mLeft->GetPos().y);
				mRight->SetPos(600.f, mRight->GetPos().y);
			}

			SetCurPatton(eBossPatton::Patton1);
			mLeft->SetCurPattonState(ePattonState::READY);
			mPatternProgress = true;
		}*/
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
	bool LeianaControler::Dash(bool in)
	{
		Vector2 pos = mLeft->GetPos();
		mLeft->GetComponent<Rigidbody>()->SetSquare(2);
		mRight->GetComponent<Rigidbody>()->SetSquare(2);
		if (in)
		{
			if (mLeft->GetPos().x < mRight->GetPos().x)
			{
				if (mLeft->GetPos().x >= 1000 + 1)
					return true;

				mLeft->GetComponent<Animator>()->Play(L"R_Dash");
				mRight->GetComponent<Animator>()->Play(L"L_Dash");

				if (mLeft->GetPos().x < 1000 + 1)
				{
					mLeft->GetComponent<Rigidbody>()->AddForce(1000.f, 0.f);
					mRight->GetComponent<Rigidbody>()->AddForce(-1000.f, 0.f);
				}
			}
			else
			{
				if (mLeft->GetPos().x <= 1900)
					return true;

				mLeft->GetComponent<Animator>()->Play(L"L_Dash");
				mRight->GetComponent<Animator>()->Play(L"R_Dash");

				if (mLeft->GetPos().x > 1900)
				{
					mLeft->GetComponent<Rigidbody>()->AddForce(-1000.f, 0);
					mRight->GetComponent<Rigidbody>()->AddForce(1000.f, 0);
				}
			}
		}
		else
		{
			if (mLeft->GetPos().x < mRight->GetPos().x)
			{
				if (mLeft->GetPos().x <= 169)
					return true;

				mLeft->GetComponent<Animator>()->Play(L"L_Dash");
				mRight->GetComponent<Animator>()->Play(L"R_Dash");

				if (mLeft->GetPos().x > 169)
				{
					mLeft->GetComponent<Rigidbody>()->AddForce(-1000.f, 0000.f);
					mRight->GetComponent<Rigidbody>()->AddForce(1000.f, 0000.f);
				}
			}
			else
			{
				if (mLeft->GetPos().x >= 2200)
					return true;

				mLeft->GetComponent<Animator>()->Play(L"R_Dash");
				mRight->GetComponent<Animator>()->Play(L"L_Dash");

				if (mLeft->GetPos().x < 2200)
				{
					mLeft->GetComponent<Rigidbody>()->AddForce(-1000.f, 0000.f);
					mRight->GetComponent<Rigidbody>()->AddForce(1000.f, 000.f);
				}
			}
		}

		return false;
	}
	void LeianaControler::PushBoss(Scene* scene)
	{
		scene->AddGameObject(mLeft, eColliderLayer::BossMonster);
		scene->AddGameObject(mRight, eColliderLayer::BossMonster);
	}
}