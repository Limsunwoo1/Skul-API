#include "Sword_Monster.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Input.h"
#include "EventManager.h"

#include "Image.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Time.h"
#include "Application.h"
#include "SceneManager.h"
#include "Scene.h"
#include "MainPlayer.h"
#include "CollisionManager.h"
#include "PlayerBase.h"


namespace sw
{
	SwordMonster::SwordMonster()
		: MonsterBase()
	{
		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		mAnimator->CreatAnimations(L"R_SwordMonster_Idle", L"..\\Resource\\Animation\\Monster\\2_Stage\\R_SwordMonster\\Idle", Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(L"L_SwordMonster_Idle", L"..\\Resource\\Animation\\Monster\\2_Stage\\L_SwordMonster\\Idle", Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(L"R_SwordMonster_Move", L"..\\Resource\\Animation\\Monster\\2_Stage\\R_SwordMonster\\Move", Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(L"L_SwordMonster_Move", L"..\\Resource\\Animation\\Monster\\2_Stage\\L_SwordMonster\\Move", Vector2::Zero, 0.15f);

		mAnimator->CreatAnimations(L"R_SwordMonster_Attack", L"..\\Resource\\Animation\\Monster\\2_Stage\\R_SwordMonster\\Attack", Vector2(0.f, 10.f), 0.25f);
		mAnimator->CreatAnimations(L"L_SwordMonster_Attack", L"..\\Resource\\Animation\\Monster\\2_Stage\\L_SwordMonster\\Attack", Vector2(0.f, 10.f), 0.25f);

		mAnimator->CreatAnimations(L"R_SwordMonster_Hit", L"..\\Resource\\Animation\\Monster\\2_Stage\\R_SwordMonster\\Hit", Vector2::Zero, 0.1f);
		mAnimator->CreatAnimations(L"L_SwordMonster_Hit", L"..\\Resource\\Animation\\Monster\\2_Stage\\L_SwordMonster\\Hit", Vector2::Zero, 0.15f);

		mAnimator->Play(L"R_SwordMonster_Idle", true);

		Rigidbody* rigdbody = AddComponent<Rigidbody>();
		rigdbody->SetGround(false);
		rigdbody->SetOwner(this);

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(100.f, 100.f));

		mStaring.BoxOffset = Vector2(0.0f,-30.f);
		mStaring.BoxScale = Vector2(400.f, 50.f);

		mAttackcollider.BoxOffset = Vector2(0.0f, -30.f);
		mAttackcollider.BoxScale = Vector2(70.f, 70.f);

		mDelta = 3.0f;
		mMaxDelta = 3.0f;
	}
	SwordMonster::~SwordMonster()
	{
		GameObject::~GameObject();
	}

	void SwordMonster::Tick()
	{
		GameObject::Tick();
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
				//PlayerBase* player = dynamic_cast<PlayerBase*>(object);
				//mTarget = player->GetParent();
				mTarget = object;
				break;
			}
		}

	}

	void SwordMonster::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);


		pos = pos + mStaring.BoxOffset;
		Vector2 boxscale = mStaring.BoxScale;

		HPEN oldpen = (HPEN)SelectObject(hdc, Application::GetInstance().GetPen(ePenColor::Blue));
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, Application::GetInstance().GetBrush(eBrushColor::Transparent));

		if(mDirction)
			Rectangle(hdc, pos.x, pos.y
				, pos.x + boxscale.x, pos.y + boxscale.y);
		else
			Rectangle(hdc, pos.x - boxscale.x, pos.y
				, pos.x, pos.y + boxscale.y);

		SelectObject(hdc, oldpen);
		SelectObject(hdc, oldbrush);

		GameObject::Render(hdc);
	}

	void SwordMonster::OnCollisionEnter(Collider* other)
	{
		
	}
	void SwordMonster::OnCollisionStay(Collider* other)
	{

	}
	void SwordMonster::OnCollisionExit(Collider* other)
	{

	}

	void SwordMonster::OnCollisionEnter()
	{
		
	}
	void SwordMonster::OnCollisionStay()
	{

	}
	void SwordMonster::OnCollisionExit()
	{

	}

	void SwordMonster::IDLE()
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
				mAnimator->Play(L"R_SwordMonster_Idle");
			else
				mAnimator->Play(L"L_SwordMonster_Idle");

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
	void SwordMonster::Attack()
	{
		if (mState[(int)eMonsterState::ATTACK] == false)
		{
			if (mDirction)
				mAnimator->Play(L"R_SwordMonster_Attack");
			else
				mAnimator->Play(L"L_SwordMonster_Attack");

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

				int a = 0;
			}
			else
			{
				temp = CollisionManager::GetInstance()->
					MomentCollsion(Box{ scale, pos }, mTarget, mDirction);

				int a = 0;
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

	void SwordMonster::Move()
	{
		mDelta += Time::GetInstance()->DeltaTime();

		if (mState[(int)eMonsterState::MOVE] == false)
		{
			if (mDirction)
				mAnimator->Play(L"R_SwordMonster_Move", true);
			else
				mAnimator->Play(L"L_SwordMonster_Move", true);

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
			
			if (abs(distance.x) <= 100 && abs(distance.y) <= 50)
			{
				mPrevState = mCurState;
				mCurState = eMonsterState::ATTACK;
				mDelta = 0.0f;
				mState[(int)eMonsterState::MOVE] = false;
			}
		}
	}
	void SwordMonster::Hit()
	{
		mDelta += Time::GetInstance()->DeltaTime();
		if (mState[(int)eMonsterState::HIT] == false)
		{
			if (mDirction)
				mAnimator->Play(L"R_SwordMonster_Hit", true);
			else
				mAnimator->Play(L"L_SwordMonster_Hit", true);

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
}
