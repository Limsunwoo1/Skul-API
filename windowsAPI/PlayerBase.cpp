#include "PlayerBase.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"
#include "AttackCollider.h"

#include "Scene.h"
#include "Image.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "StateHandle.h"
#include "Shadow.h"


namespace sw
{
	PlayerBase::PlayerBase()
	{
		int a = 0;
		//SetPos({ 100.0f, 100.0f });
		//SetScale({ 5.f, 5.f});

		//// Animation ����
		//mAnimator = new Animator();
		//mAnimator->CreatAnimations(L"R_IDLE", L"..\\Resource\\Animation\\BasicSkul\\R_Idle", Vector2(-20.f, 0.f), 0.25f);
		//mAnimator->CreatAnimations(L"L_IDLE", L"..\\Resource\\Animation\\BasicSkul\\L_Idle", Vector2(20.f, 0.f), 0.3f);

		//mAnimator->CreatAnimations(L"R_RUN", L"..\\Resource\\Animation\\BasicSkul\\R_RUN", Vector2::Zero, 0.05f);
		//mAnimator->CreatAnimations(L"L_RUN", L"..\\Resource\\Animation\\BasicSkul\\L_RUN", Vector2::Zero, 0.05f);

		//mAnimator->CreatAnimations(L"R_JUMP", L"..\\Resource\\Animation\\BasicSkul\\R_JUMP", Vector2::Zero, 0.2f);
		//mAnimator->CreatAnimations(L"L_JUMP", L"..\\Resource\\Animation\\BasicSkul\\L_JUMP", Vector2::Zero, 0.2f);

		//mAnimator->CreatAnimations(L"R_Drop", L"..\\Resource\\Animation\\BasicSkul\\R_Drop", Vector2::Zero, 0.2f);
		//mAnimator->CreatAnimations(L"L_Drop", L"..\\Resource\\Animation\\BasicSkul\\L_Drop", Vector2::Zero, 0.2f);

		//mAnimator->CreatAnimations(L"R_Dash", L"..\\Resource\\Animation\\BasicSkul\\R_Dash", Vector2::Zero, 0.2f);
		//mAnimator->CreatAnimations(L"L_Dash", L"..\\Resource\\Animation\\BasicSkul\\L_Dash", Vector2::Zero, 0.2f);

		//mAnimator->CreatAnimations(L"R_AttackA", L"..\\Resource\\Animation\\BasicSkul\\R_AttackA", Vector2(-20.f, 9.f), 0.15f);
		//mAnimator->CreatAnimations(L"R_AttackB", L"..\\Resource\\Animation\\BasicSkul\\R_AttackB", Vector2(-20.f, 0.f), 0.15f);

		//mAnimator->CreatAnimations(L"L_AttackA", L"..\\Resource\\Animation\\BasicSkul\\L_AttackA", Vector2(20.f, 0.f), 0.15f);
		//mAnimator->CreatAnimations(L"L_AttackB", L"..\\Resource\\Animation\\BasicSkul\\L_AttackB", Vector2(20.f, 0.f), 0.15f);

		//AddComponent(mAnimator);
		//AddComponent<Rigidbody>();
		//Collider* collider = AddComponent<Collider>();
		//collider->SetScale(Vector2(100.f,100.f));

		//mAnimator->Play(L"R_IDLE", true);
		//
		//mState = new StateHandle();
		//mState->SetTarget(this);
		//this->SetState(eObjectState::IDLE);

		//// Animator �� ���� �������� �ִϸ��̼� ������ ���ε�
		////animator->StartEvent() = std::bind(&Player::StartEvent, this);
		////animator->EndEvent() = std::bind(&Player::EndEvent, this);
		///*if (mAnimator->bPlayAnimation())
		//{
		//	mAnimator->CompleteEvent() = 
		//		std::bind(&Player::CompleteEvent, this);
		//}*/
		//Camera::GetInstance()->SetTarget(this);
		//mShaow = new Shadow();
		//mShaow->Initialize(L"R_DashEffect", L"..\\Resource\\Animation\\BasicSkul\\R_DashEffect\\R_DashEffect.bmp");
		//mShaow->SetTarget(this);
	}

	PlayerBase::~PlayerBase()
	{
		/*GameObject::~GameObject();
		delete mState;
		delete mShaow;*/
	}

	AttackCollider* PlayerBase::FindAttackCollider(std::wstring name)
	{
		for (AttackCollider* collider : mColliders)
		{
			if (collider->GetName() == name)
				return collider;
		}

		return nullptr;
	}

	void PlayerBase::CompleteEvent()
	{
	
	}

	void PlayerBase::Tick()
	{
		/*GameObject::Tick();
		mState->Tick();

		if (mShaow)
			mShaow->Tick();*/

	}

	void PlayerBase::Render(HDC hdc)
	{
		/*Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		Rectangle(hdc, pos.x - 5, pos.y - 5, pos.x + 5, pos.y + 5);

		if (mShaow)
			mShaow->Render(hdc);

		GameObject::Render(hdc);*/

	}

	void PlayerBase::OnCollisionEnter(Collider* other)
	{
	}
	void PlayerBase::OnCollisionStay(Collider* other)
	{
	}
	void PlayerBase::OnCollisionExit(Collider* other)
	{
	}
	void PlayerBase::ShadowEffect()
	{
	}
	void PlayerBase::SetState(eObjectState type)
	{
		mState->SetState(type);
	}
	eObjectState PlayerBase::GetState()
	{
		return mState->GetStateType();
	}
	eObjectState PlayerBase::GetPrevState()
	{
		return mState->GetPrevStateType();
	}
}
