#include "MonsterBase.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "EventManager.h"

#include "Image.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Time.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Application.h"

namespace sw
{
	MonsterBase::MonsterBase()
		: mImage(nullptr)
		, mAnimator(nullptr)
		, mTarget(nullptr)
		, mCurState(eMonsterState::IDLE)
		, mPrevState(mCurState)
		, mDirction(true)
		, mColCount(0)
		, RName(L"")
		, LName(L"")
		, mAttackX(0)
		, mAttackY(0)
		, mArmer(false)

	{
		for (int i = 0; i < (int)eMonsterState::END; ++i)
		{
			mState[i] = false;
		}
		mState[(int)eMonsterState::IDLE] = true;

		Rigidbody* rigdbody = AddComponent<Rigidbody>();
		rigdbody->SetGround(false);
		rigdbody->SetOwner(this);

		mDelta = 3.0f;
		mMaxDelta = 3.0f;
	}
	MonsterBase::~MonsterBase()
	{
		GameObject::~GameObject();
	}

	void MonsterBase::Tick()
	{
		Branch();
		Staring();
		GameObject::Tick();
		CheckGround();
	}

	void MonsterBase::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		pos = pos + mStaring.BoxOffset;
		Vector2 boxscale = mStaring.BoxScale;

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
	}
	void MonsterBase::IDLE()
	{
		static int i = 0;
		if (i >= 2)
		{
			if (mDirction)
				mDirction = false;
			else
				mDirction = true;

			i = 0;
		}

		mDelta += Time::GetInstance()->DeltaTime();
		if (mState[(int)eMonsterState::IDLE] == false)
		{
			if (mDirction)
				mAnimator->Play(RName + L"Idle");
			else
				mAnimator->Play(LName + L"Idle");

			mState[(int)eMonsterState::IDLE] = true;
			i++;
		}

		if (mDelta < mMaxDelta)
			return;

		mDelta = 0.0f;
		mPrevState = mCurState;
		mCurState = eMonsterState::MOVE;
		mState[(int)eMonsterState::IDLE] = false;
	}
	void MonsterBase::Attack()
	{
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
				// Ãæµ¹
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
		}

		Rigidbody* rigidbody = this->GetComponent<Rigidbody>();
		if (mTarget == nullptr)
		{
			if (mDirction)
				rigidbody->AddForce(Vector2(100.f, 0.0f));
			else
				rigidbody->AddForce(Vector2(-100.f, 0.0f));

			if (mDelta > 5.0f)
			{
				mState[(int)eMonsterState::MOVE] = false;
				mDelta = 0.0f;
				mPrevState = mCurState;
				mCurState = eMonsterState::IDLE;
			}
		}
		else
		{
			Vector2 distance = mTarget->GetPos() - GetPos();
			if (distance.x < 0)
			{
				if (mDirction)
				{
					mDirction = false;
					mState[(int)eMonsterState::MOVE] = false;
				}

				rigidbody->AddForce(Vector2(-200.f, 0.0f));
			}
			else
			{
				if (!mDirction)
				{
					mDirction = true;
					mState[(int)eMonsterState::MOVE] = false;
				}

				rigidbody->AddForce(Vector2(200.f, 0.0f));
			}

			if (abs(distance.x) <= mAttackX && abs(distance.y) <= mAttackY)
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
				mAnimator->Play(RName + L"Hit", true);
			else
				mAnimator->Play(LName + L"Hit", true);

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
		Scene* scene = SceneManager::GetInstance()->GetPlayScene();
		std::vector<GameObject*>& objects = scene->GetGameObject(eColliderLayer::Player);
		Vector2 pos = GetPos();
		pos = pos + mStaring.BoxOffset;

		for (GameObject* object : objects)
		{
			if (mTarget != nullptr)
				break;

			bool temp = false;
			if (mDirction)
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ mStaring.BoxScale, pos }, object);
			}
			else
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ mStaring.BoxScale, pos }, object, false);
			}

			if (temp)
			{
				mTarget = object;
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
		Scene* scene = SceneManager::GetInstance()->GetPlayScene();
		const std::vector<GameObject*>& objects = scene->GetGameObject(eColliderLayer::Ground);
		Collider* col = GetComponent<Collider>();
		Vector2 CPos = col->GetPos();
		Vector2 CScale = col->GetScale();

		float under = CPos.y + (CScale.y * 0.5f);
		std::vector<GameObject*> temp;
		for (GameObject* object : objects)
		{
			float over = object->GetPos().y - (object->GetScale().y * 0.5f);
			if (fabs(under - over) < 3)
			{
				temp.push_back(object);
			}
		}

		for (GameObject* object : temp)
		{
			Rigidbody* rigid = GetComponent<Rigidbody>();
			Vector2 objPos = object->GetPos();
			Vector2 objScale = object->GetScale();
			if (CPos.x > objPos.x + (objScale.x * 0.5f))
			{
				if (mTarget == nullptr)
				{
					if (mDirction)
						mDirction = false;
					
				}
				CPos.x = objPos.x + (objScale.x * 0.5f);
			}
			if (CPos.x < objPos.x - (objScale.x * 0.5f))
			{
				if (!mDirction)
					mDirction = true;
				CPos.x = objPos.x - (objScale.x * 0.5f);
			}

			SetPos(CPos);
		}
	}
}
