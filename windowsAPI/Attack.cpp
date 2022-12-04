#include "Attack.h"
#include "Move.h"
#include "StateHandle.h"
#include "Animator.h"
#include "Animation.h"
#include "Time.h"
#include "Input.h"
#include "AttackCollider.h"
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"

namespace sw
{
	Attack::Attack()
		: State()
		, mDelta(0.0f)
		, mAttackCount(0)
		, bInput(false)
	{
		/*mR_AttackSequence.push_back(L"R_AttackA");
		mR_AttackSequence.push_back(L"R_AttackB");

		mL_AttackSequence.push_back(L"L_AttackA");
		mL_AttackSequence.push_back(L"L_AttackB");*/
	}

	Attack::~Attack()
	{

	}

	void Attack::Start(PlayerBase* target)
	{
		SetTarget(target);
		StartCollider();
		SetStartAnimation();
	}
	void Attack::Run()
	{
		mDelta += Time::GetInstance()->DeltaTime();

		SetAnimation();
	}

	void Attack::End()
	{
		for (GameObject* object : mTemp)
		{
			object->OnCollisionExit();
		}
		mTemp.clear();

		mColliderBox.BoxOffset = Vector2::Zero;
		mColliderBox.BoxScale = Vector2::Zero;

		GetTarget()->SetColliderBox(mColliderBox);
	}

	void Attack::StartCollider()
	{
		Scene* scene = SceneManager::GetInstance()->GetPlayScene();
		const std::vector<GameObject*>& objects = scene->GetGameObject(eColliderLayer::Monster);
		PlayerBase* player = GetTarget();
		eObjectState state = player->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (state == eObjectState::LEFT)
			mColliderBox = player->GetColliders(mL_AttackSequence[mAttackCount]);
		else if (state == eObjectState::RIGHT)
			mColliderBox = player->GetColliders(mR_AttackSequence[mAttackCount]);

		Vector2 pos = player->GetPos();
		Vector2 scale = mColliderBox.BoxScale;
		Vector2 offset = mColliderBox.BoxOffset;

		// 렌더용 현제 충돌체 정보
		player->SetColliderBox(mColliderBox);

		for (GameObject* object : objects)
		{
			bool bCollision = CollisionManager::GetInstance()->CheckCollision(Box{ scale, pos + offset},object);
			if (!bCollision)
				continue;

			mTemp.push_back(object);
			object->OnCollisionEnter();
		}
	}

	void Attack::SetStartAnimation()
	{
		// 방향설정
		PlayerBase* player = GetTarget();
		eObjectState state = player->GetStateHandle()->GetState<Move>(eObjectState::LEFT)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (state == eObjectState::LEFT)
			animator->Play(mL_AttackSequence[mAttackCount], false);
		else if (state == eObjectState::RIGHT)
			animator->Play(mR_AttackSequence[mAttackCount], false);

		mDelta = 0.0f;
	}

	void Attack::SetAnimation()
	{
		PlayerBase* player = GetTarget();
		Animator* animator = player->GetComponent<Animator>();
		if (mDelta < 0.4f)
		{
			// 이동하면서 공격 추가
			PlayerBase* player = GetTarget();
			StateHandle* statehandle = player->GetStateHandle();
			eObjectState state = player->GetStateHandle()->
				GetState<Move>(eObjectState::LEFT)->GetDirtion();

			if (KEY_PRESSE(eKeyCode::LEFT) && state == eObjectState::LEFT)
			{
				statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::LEFT);
				player->GetComponent<Rigidbody>()->AddForce(Vector2(-30.f, 0.0f));
			}
			else if (KEY_PRESSE(eKeyCode::RIGHT) && state == eObjectState::RIGHT)
			{
				statehandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::RIGHT);
				player->GetComponent<Rigidbody>()->AddForce(Vector2(30.f, 0.0f));
			}
			
			if (KEY_DOWN(eKeyCode::X))
				bInput = true;
			return;
		}

		if (animator->isComplete())
		{
			End();
			mDelta = 0.0f;
			player->SetState(eObjectState::IDLE);
			return;
		}

		if (bInput)
		{
			++mAttackCount;
			bInput = false;

			if (mAttackCount > player->GetMaxAttackCount())
				return;

			mDelta = 0.0f;
			End();
			Start(GetTarget());
		}
		

		/*End();
		mDelta = 0.0f;
		GetTarget()->SetState(eObjectState::IDLE);*/
	}
}