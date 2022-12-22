#include "Attack.h"
#include "Move.h"
#include "StateHandle.h"
#include "Animator.h"
#include "Time.h"
#include "Input.h"
#include "EffectObject.h"
#include "CollisionManager.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "MonsterBase.h"

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

		if (mAttackCount <= GetTarget()->GetMaxAttackCount())
		{
			StartCollider();
			SetStartAnimation();
		}
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
			object->GetComponent<Collider>()->OnCollisionExit();
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
		Animator* animator = player->GetComponent<Animator>();
		bool state = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();

		if (!state)
			mColliderBox = player->GetColliders(mL_AttackSequence[mAttackCount]);
		else if (state)
			mColliderBox = player->GetColliders(mR_AttackSequence[mAttackCount]);

		Vector2 pos = player->GetPos();
		Vector2 scale = mColliderBox.BoxScale;
		Vector2 offset = mColliderBox.BoxOffset;

		// 렌더용 현제 충돌체 정보
		player->SetColliderBox(mColliderBox);
		// 충돌체크
		for (GameObject* object : objects)
		{
			Collider* collider = object->GetComponent<Collider>();
			collider->SetPos(object->GetPos());

			bool bCollision = CollisionManager::GetInstance()->CheckCollision(Box{ scale, pos + offset},object);
			if (!bCollision)
				continue;

			mTemp.push_back(object);
			collider->OnCollisionEnter();

			// 플레이어에 공격시 피격이펙트
			GetTarget()->OnAttackEffect(object);

			MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
			if (monster != nullptr)
			{
				eMonsterState type = monster->GetState();
				if (monster->GetSuperArmer())
				{
					monster->Hit();
					continue;
				}
				monster->SetAble(type, false);
				monster->SetDirction(!state);  // 공격 방향으로 피격대상 방향변경
				monster->SetState(eMonsterState::HIT);
				monster->SetDelta(0.0f);
			}
		}
	}

	void Attack::SetStartAnimation()
	{
		// 방향설정
		PlayerBase* player = GetTarget();
		bool state = player->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = player->GetComponent<Animator>();

		if (!state)
			animator->Play(mL_AttackSequence[mAttackCount], false);
		else if (state)
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
			bool state = player->GetStateHandle()->
				GetState<Move>(ePlayerState::MOVE)->GetDirtion();

			if (KEY_PRESSE(eKeyCode::LEFT) && state == false)
			{
				statehandle->GetState<Move>(ePlayerState::MOVE)->SetDirtion(false);
				player->GetComponent<Rigidbody>()->AddForce(Vector2(-30.f, 0.0f));
			}
			else if (KEY_PRESSE(eKeyCode::RIGHT) && state == true)
			{
				statehandle->GetState<Move>(ePlayerState::MOVE)->SetDirtion(true);
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
			player->SetState(ePlayerState::IDLE);
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