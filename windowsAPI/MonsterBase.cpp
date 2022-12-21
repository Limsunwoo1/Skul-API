#include "MonsterBase.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "EventManager.h"
#include "UtilLog.h"

#include "Image.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Time.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Application.h"
#include "ResourceManager.h"
#include "Ground.h"
#include <random>

namespace sw
{
	std::random_device random;
	std::mt19937 gen(random());
	std::uniform_int_distribution<int> delay(2, 4);
	std::uniform_int_distribution<int> force(200, 1000);

	MonsterBase::MonsterBase()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mTarget(nullptr)
		, mGround(nullptr)
		, mCurState(eMonsterState::IDLE)
		, mPrevState(mCurState)
		, mDirction(true)
		, RName(L"")
		, LName(L"")
		, mAttackX(0)
		, mAttackY(0)
		, mArmer(false)
		, mStaring(false)
		, mHold(false)
		, mAttackCooltime(0.0f)
		, mAttackCooltimeMax(0.0f)
		, mDelay(0.0f)
		, mDistance(0.0f)
		, mStaringTime(0.0f)
		, mMovement(0)
		, mPrevPos(Vector2::Zero)

	{
		for (int i = (int)eMonsterState::IDLE; i < (int)eMonsterState::END; ++i)
		{
			mState[i] = false;
		}

		Rigidbody* rigdbody = AddComponent<Rigidbody>();
		rigdbody->SetGround(false);
		rigdbody->SetOwner(this);

		mDelta = 3.0f;
		mMaxDelta = 3.0f;

		mImage = ResourceManager::GetInstance()->
			Load<Image>(L"StraingMark", L"..\\Resource\\Image\\Exclamation mark.bmp");

		std::random_device random;
		std::mt19937 gen(random());
		std::uniform_int_distribution<int> delay(2,6);
		std::uniform_int_distribution<int> force(2,6);

		rgen = gen;
		rDelay = delay;
		rDistance = force;

		mPrevPos = GetPos();
	}

	MonsterBase::~MonsterBase()
	{
		GameObject::~GameObject();
	}

	void MonsterBase::Tick()
	{
		mAttackCooltime += Time::GetInstance()->DeltaTime();
		if (mHold)
			Hold();

		Staring();
		Branch();
		GameObject::Tick();
		CheckGround();

		// 이전위치 저장
		mPrevPos = GetPos();
	}

	void MonsterBase::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		pos = pos + mStaringCollider.BoxOffset;
		Vector2 boxscale = mStaringCollider.BoxScale;

		HPEN oldpen = (HPEN)SelectObject(hdc, Application::GetInstance().GetPen(ePenColor::Blue));
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));

		/*if(mDirction)
			Rectangle(hdc, pos.x, pos.y
				, pos.x + boxscale.x, pos.y + boxscale.y);
		else
			Rectangle(hdc, pos.x - boxscale.x, pos.y
				, pos.x, pos.y + boxscale.y);*/

		SelectObject(hdc, oldpen);
		SelectObject(hdc, oldbrush);

		GameObject::Render(hdc);

		if (mStaring)
		{
			Collider* collider = GetComponent<Collider>();
			TransparentBlt(hdc, pos.x, pos.y - (collider->GetScale().y * 0.5f) - 20.f
				, 40.f, 40.f
				, mImage->GetDC()
				, 0.0f, 0.0f
				, mImage->GetWidth(), mImage->GetHeight()
				, RGB(255, 0, 255));
		}
	}
	void MonsterBase::IDLE()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		if (mState[(int)eMonsterState::IDLE] == false)
		{
			if (mDirction)
				mAnimator->Play(RName + L"Idle");
			else
				mAnimator->Play(LName + L"Idle");

			mState[(int)eMonsterState::IDLE] = true;
			mDelay = rDelay(rgen);
		}
		if (mTarget != nullptr)
			mDelay = 3.0f;
		if (mDelta < mDelay)
			return;

		mDelta = 0.0f;
		mPrevState = mCurState;
		mCurState = eMonsterState::MOVE;
		mState[(int)eMonsterState::IDLE] = false;
	}
	void MonsterBase::Attack()
	{
		mAttackCooltime = 0.0f;
		if (mState[(int)eMonsterState::ATTACK] == false)
		{
			if (mDirction)
				mAnimator->Play(RName + L"Attack");
			else
				mAnimator->Play(LName + L"Attack");

			mState[(int)eMonsterState::ATTACK] = true;

			if (mTarget == nullptr)
			{
				mPrevState = mCurState;
				mCurState = eMonsterState::IDLE;
				mState[(int)eMonsterState::ATTACK] = false;
				return;
			}

			Vector2 pos = GetPos() + mAttackcollider.BoxOffset;
			Vector2 scale = mAttackcollider.BoxScale;
			bool temp = false;
			if (mDirction)
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ scale, pos }, mTarget);
			}
			else
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ scale, pos }, mTarget, mDirction);

			}

			if (temp)
			{
				int a = 0;
				// 충돌
			}
		}

		if (mAnimator->isComplete())
		{
			mPrevState = mCurState;
			mCurState = eMonsterState::IDLE;
			mState[(int)eMonsterState::ATTACK] = false;
		}
	}
	void MonsterBase::Move()
	{
		mDelta += Time::GetInstance()->DeltaTime();

		if (mState[(int)eMonsterState::MOVE] == false)
		{
			if (mDirction)
				mAnimator->Play(RName + L"Move", true);
			else
				mAnimator->Play(LName + L"Move", true);

			mState[(int)eMonsterState::MOVE] = true;

			mMovement = 0;
			mDistance = rDistance(rgen) * 100.f;
		}

		Rigidbody* rigidbody = this->GetComponent<Rigidbody>();
		if (mTarget == nullptr)
		{
			mMovement += fabs(mPrevPos.x - GetPos().x);
			if (mDirction)
				rigidbody->AddForce(Vector2(100.f, 0.0f));
			else
				rigidbody->AddForce(Vector2(-100.f, 0.0f));
			
			if (mMovement > mDistance)
			{
				mState[(int)eMonsterState::MOVE] = false;
				mDelta = 0.0f;
				mPrevState = mCurState;
				mCurState = eMonsterState::IDLE;
			}
		}
		else
		{
			Vector2 cPos = mTarget->GetComponent<Collider>()->GetPos();
			Vector2 cScal = mTarget->GetComponent<Collider>()->GetScale();

			Vector2 mColPos = GetComponent<Collider>()->GetPos();
			Vector2 mColScale = GetComponent<Collider>()->GetScale();

			Vector2 flen = cPos - mColPos;
			float fscale = ((cScal.x * 0.5f) + (mColScale.x * 0.5f));
			if (flen.x < 0)
			{
				if (fabs(flen.x) >= fscale)
					rigidbody->AddForce(Vector2(-200.f, 0.0f));
				else
				{
					mState[(int)eMonsterState::MOVE] = false;
					mPrevState = mCurState;
					mCurState = eMonsterState::IDLE;
					mDelta = 0.0f;
				}
			}
			else
			{
				if (fabs(flen.x) > fscale)
					rigidbody->AddForce(Vector2(200.f, 0.0f));
				else
				{
					mState[(int)eMonsterState::MOVE] = false;
					mPrevState = mCurState;
					mCurState = eMonsterState::IDLE;
					mDelta = 0.0f;
				}
			}

			if (mAttackCooltime < mAttackCooltimeMax)
				return;

			if (abs(flen.x) <= mAttackX && abs(flen.y) <= mAttackY)
			{
				mPrevState = mCurState;
				mCurState = eMonsterState::ATTACK;
				mDelta = 0.0f;
				mState[(int)eMonsterState::MOVE] = false;
			}
		}
	}
	void MonsterBase::Hit()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		if (mState[(int)eMonsterState::HIT] == false)
		{
			if (mDirction)
				mAnimator->Play(RName + L"Hit");
			else
				mAnimator->Play(LName + L"Hit");

			Rigidbody* rigidbody = this->GetComponent<Rigidbody>();

			if (mDirction)
				rigidbody->AddForce(Vector2(-1000.f, 0.f));
			else
				rigidbody->AddForce(Vector2(1000.f, 0.f));

			mState[(int)eMonsterState::HIT] = true;
		}

		if (mDelta > 1.0f)
		{
			mDelta = 0.0f;
			mState[(int)eMonsterState::HIT] = false;
			mPrevState = mCurState;
			mCurState = eMonsterState::MOVE;
		}
	}
	void MonsterBase::Staring()
	{
		if (mStaring)
			mStaringTime += Time::GetInstance()->DeltaTime();
		if (mStaringTime > 2.0f)
			mStaring = false;
		if (mTarget)
			return;

		Scene* scene = SceneManager::GetInstance()->GetPlayScene();
		std::vector<GameObject*>& objects = scene->GetGameObject(eColliderLayer::Player);
		Vector2 pos = GetPos();
		pos = pos + mStaringCollider.BoxOffset;

		for (GameObject* object : objects)
		{
			bool temp = false;
			if (mDirction)
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ mStaringCollider.BoxScale, pos }, object);
			}
			else
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ mStaringCollider.BoxScale, pos }, object, false);
			}

			if (temp)
			{
				mStaring = true;
				mTarget = object;

				mPrevState = mCurState;
				mState[(int)mCurState] = false;
				SetState(eMonsterState::IDLE);
				break;
			}
		}
	}

	void MonsterBase::Branch()
	{
		switch (mCurState)
		{
		case sw::eMonsterState::IDLE:
		{
			IDLE();
		}
		break;

		case sw::eMonsterState::MOVE:
		{
			Move();
		}
		break;

		case sw::eMonsterState::ATTACK:
		{
			Attack();
		}
		break;

		case sw::eMonsterState::HIT:
		{
			Hit();
		}
		break;

		case sw::eMonsterState::END:
		{

		}
		break;
		}
	}

	void MonsterBase::CheckGround()
	{
		if (mGround == nullptr)
			return;

		Collider* col = GetComponent<Collider>();
		Vector2 cPos = col->GetPos();
		Vector2 cScale = col->GetScale();

		Vector2 gPos = mGround->GetPos();
		Vector2 gSclae = mGround->GetScale();

		float right = cPos.x + (cScale.x * 0.5f);
		float left = cPos.x - (cScale.x * 0.5f);

		float Delta = 0.0f;

		// 로직변경필요
		// 코드 개선필요
		Vector2 pos = cPos;
		if (gPos.x + (gSclae.x * 0.5f) < right
			|| gPos.x - (gSclae.x * 0.5f) > left)
		{
			if (cPos.x > gPos.x)
				pos.x = gPos.x + (gSclae.x * 0.5f) - (cScale.x * 0.5f + 1.0f);
			else if (cPos.x < gPos.x)
				pos.x = gPos.x - (gSclae.x * 0.5f) + (cScale.x * 0.5f + 1.0f);
			SetPos(pos);

			if (mTarget == nullptr)
			{
				if (mDirction)
					mDirction = false;
				else
					mDirction = true;
			}

			mState[(UINT32)mCurState] = false;
			mPrevState = mCurState;
			SetDelta(Delta);
			SetState(eMonsterState::IDLE);
		}

		if (mCurState == eMonsterState::ATTACK)
			return;
		if (mCurState == eMonsterState::IDLE)
			return;

		if(mTarget != nullptr)
		{
			if (mDirction && mTarget->GetPos().x < pos.x)
			{
				mState[(UINT32)mCurState] = false;
				mDirction = false;
				Delta += mMaxDelta;
				SetDelta(Delta);
			}
			else if (!mDirction && mTarget->GetPos().x > pos.x)
			{
				mState[(UINT32)mCurState] = false;
				mDirction = true;
				Delta += mMaxDelta;
				SetDelta(Delta);
			}
		}
	}

	void MonsterBase::OnCollisionEnter(Collider* other)
	{
		if (mGround == nullptr)
		{
			Ground* ground = dynamic_cast<Ground*>(other->GetOwner());
			if (ground != nullptr)
				mGround = ground;
		}
	}

	void MonsterBase::Hold()
	{
		mState[(UINT32)mCurState] = false;
		mPrevState = mCurState;
		SetDelta(0.0f);
		SetState(eMonsterState::IDLE);
		mHold = false;
	}
}
