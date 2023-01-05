#include "LeianaControler.h"
#include "LeianaBoss.h"
#include "LeianaBossRight.h"
#include "Scene.h"
#include "Time.h"
#include "MainPlayer.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "StaticObject.h"
#include "EventManager.h"
#include "UIManager.h"
#include "Panel.h"
#include "HpBar.h"

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
		, mModeChange(false)
		, mBossSceneEnd(false)
		, mEnddingSound(false)
		, mPattonCount(0.f)
	{
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
		MyGenericAnimator.Update(Time::GetInstance()->DeltaTime());

		if(mLeft)
			SetHp(mLeft->GetHp());
		if (mRight)
			mRight->SetHp(GetHp());

		if (GetHp() <= 0 && !mBossSceneEnd)
		{
			OuttroIn();
			mBossSceneEnd = true;
			mKing->SetEndding(true);
		}
		if (mBossSceneEnd)
			return;

		Brunch();
	}
	void LeianaControler::Initialize()
	{
		mLeft = new LeianaBoss();
		mLeft->SetOwer(this);
		mLeft->SetPower(GetPower());
		mLeft->Initialize();

		mRight = new LeianaBossRight();
		mRight->SetOwer(this);
		mRight->SetPower(GetPower());
		mRight->Initialize();

		SetHp(mLeft->GetHp());
		mRight->SetHp(GetHp());

		// 미들 킹 인잇
		mKing = new KingObject;
		mKing->SetPos(1200.f, 305.f);

		mEnddingBack = new StaticObject(L"StaticObject19");
		mEnddingBack->SetScale(6.0f, 6.0f);
		mEnddingBack->GetComponent<Animator>()->SetOnRender(false);

		// UI;
		mHpPanel = new Panel(eUIType::Boss_Panel);
		mHpPanel->ImageLoad(L"BossPanel", L"..\\Resource\\Ui\\Player_Subbar_Frame 복사.bmp");
		mHpPanel->SetPos(Vector2(800.f, 100.f));
		mHpPanel->SetSize(Vector2(900, 30.f));
		UIManager::GetInstance()->SetUiInstance(eUIType::Boss_Panel, mHpPanel);

		HpBar* mHpBar = new HpBar(eUIType::BossHp);
		mHpBar->ImageLoad(L"bossHp", L"..\\Resource\\Ui\\boss_SubBar3.bmp");
		mHpBar->SetPos(Vector2(500.f, 500.f));
		mHpBar->SetSize(Vector2(850.f, 15.f));
		mHpBar->SetTarget(mLeft);
		mHpBar->SetTargetMaxHp(GetHp());
		mHpBar->SetmaxSizeX(850.f);
		UIManager::GetInstance()->SetUiInstance(eUIType::BossHp, mHpBar);

		mHpPanel->SetChild(Vector2(-420.f, -8.f), mHpBar);
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
		if (mModeChange)
		{
			mLeft->SetScreenIn(false);
			mRight->SetScreenIn(false);

			mLeft->SetScreenOut(false);
			mRight->SetScreenOut(false);

			mLeft->SetDelta(0.0f);
			mRight->SetDelta(0.0f);

			mModeChange = false;
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
				//SetCurPatton(eBossPatton::Patton3);
				mLeft->SetCurPattonState(ePattonState::READY);
				mRight->SetCurPattonState(ePattonState::READY);
				mPattonCount += 1.0f;
			}

			if (!mCombeMode)
			{
				mLeft->SetScreenOut(true);
				SetCurPatton((eBossPatton)SoloPatton(gen1));
				//SetCurPatton(eBossPatton::Patton6);
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
				mModeChange = true;
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

		scene->AddGameObject(mKing, eColliderLayer::StaticObject);
		scene->AddGameObject(mEnddingBack, eColliderLayer::StaticObject);
	}
	void LeianaControler::OuttroIn()
	{
		sw::BossSound.Stop(true);

		mEnddingBack->GetComponent<Animator>()->SetOnRender(true);
		mEnddingBack->GetComponent<Animator>()->Play(L"StaticObject19");
		mEnddingBack->SetPos(1200.f, 500.f);
		mEnddingBack->SetScale(5.f, 5.f);

	

		if (MyGenericAnimator.IsRunning())
			MyGenericAnimator.Stop();

		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 255.f;
		param.DurationTime = 1.0f;

		param.DurationFunc = [this](float InCurValue)
		{
			mEnddingBack->GetComponent<Animator>()->SetAlpha(InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue)
		{
			mLeft->OffProjecTile();
			mRight->OffProjecTile();

			mLeft->GetComponent<Animator>()->SetOnRender(false);
			mRight->GetComponent<Animator>()->SetOnRender(false);

			mLeft->GetComponent<Animator>()->Play(L"LDead");
			mRight->GetComponent<Animator>()->Play(L"RDead");

			mLeft->SetPos(600.f,705.f);
			mRight->SetPos(1800.f, 705.f);

			//Dead 모션실행
			OuttroOut();
		};
		MyGenericAnimator.Start(param);
	}
	void LeianaControler::OuttroOut()
	{
		sw::LeianaDead.Play(false);
		mLeft->GetComponent<Animator>()->SetOnRender(true);
		mRight->GetComponent<Animator>()->SetOnRender(true);

		if (MyGenericAnimator.IsRunning())
			MyGenericAnimator.Stop();

		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 255.f;
		param.EndValue = 0.f;
		param.DurationTime = 1.0f;
		param.DurationFunc = [this](float InCurValue)
		{
			mEnddingBack->GetComponent<Animator>()->SetAlpha(InCurValue);
		};
		param.CompleteFunc = [this](float InCurValue)
		{
			mEnddingBack->GetComponent<Animator>()->SetOnRender(false);
			// 미들보스애니메이션 씬넘기기
			ChangeBossScene();
		};
		MyGenericAnimator.Start(param);
	}
	void LeianaControler::ChangeBossScene()
	{
		mKing->GetComponent<Animator>()->Play(L"KingSurprise");

		if (MyGenericAnimator.IsRunning())
			MyGenericAnimator.Stop();

		AnimatorParam param;
		param.AnimType = EAnimType::Linear;
		param.StartValue = 0.f;
		param.EndValue = 1.f;
		param.DurationTime = 5.0f;
		float value = 0.5f;
		param.DurationFunc = [this, value](float InCurValue)
		{
			if (InCurValue > value && !mEnddingSound)
			{
				mEnddingSound = true;
				sw::EndSound.Play(true);
			}
		};
		param.CompleteFunc = [this](float InCurValue)
		{
			EventInfo info;
			info.Type = EventType::ChangeScene;
			info.Parameter1 = new eSceneType(eSceneType::End);
			EventManager::GetInstance()->EventPush(info);

			MyGenericAnimator.Stop();
		};
		MyGenericAnimator.Start(param);
	}
}