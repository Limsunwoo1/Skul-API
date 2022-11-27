#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"

#include "Scene.h"
#include "Missile.h"
#include "Image.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "StateHandle.h"
#include "Shadow.h"


namespace sw
{
	Player::Player()
		: mSpeed(1.0f)
		, mbShadow(false)
		, mShaow(nullptr)
		, mMaxAttackCount(2)
	{
		SetPos({ 100.0f, 100.0f });
		SetScale({ 200.f, 200.0f });

		// Animation 세팅
		mAnimator = new Animator();
		mAnimator->CreatAnimations(L"R_IDLE", L"..\\Resource\\Animation\\BasicSkul\\R_IDLE", Vector2::Zero, 0.4f);
		mAnimator->CreatAnimations(L"L_IDLE", L"..\\Resource\\Animation\\BasicSkul\\L_IDLE", Vector2::Zero, 0.4f);

		mAnimator->CreatAnimations(L"R_RUN", L"..\\Resource\\Animation\\BasicSkul\\R_RUN", Vector2::Zero, 0.05f);
		mAnimator->CreatAnimations(L"L_RUN", L"..\\Resource\\Animation\\BasicSkul\\L_RUN", Vector2::Zero, 0.05f);

		mAnimator->CreatAnimations(L"R_JUMP", L"..\\Resource\\Animation\\BasicSkul\\R_JUMP", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_JUMP", L"..\\Resource\\Animation\\BasicSkul\\L_JUMP", Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Drop", L"..\\Resource\\Animation\\BasicSkul\\R_Drop", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Drop", L"..\\Resource\\Animation\\BasicSkul\\L_Drop", Vector2::Zero, 0.2f);

		mAnimator->CreatAnimations(L"R_Dash", L"..\\Resource\\Animation\\BasicSkul\\R_Dash", Vector2::Zero, 0.2f);
		mAnimator->CreatAnimations(L"L_Dash", L"..\\Resource\\Animation\\BasicSkul\\L_Dash", Vector2::Zero, 0.2f);

		AddComponent(mAnimator);
		AddComponent<Rigidbody>();
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(this->GetScale());

		mAnimator->Play(L"R_IDLE", true);
		
		mState = new StateHandle();
		mState->SetTarget(this);
		this->SetState(eObjectState::IDLE);

		// Animator 에 현재 진행중인 애니메이션 셋팅후 바인딩
		//animator->StartEvent() = std::bind(&Player::StartEvent, this);
		//animator->EndEvent() = std::bind(&Player::EndEvent, this);
		/*if (mAnimator->bPlayAnimation())
		{
			mAnimator->CompleteEvent() = 
				std::bind(&Player::CompleteEvent, this);
		}*/
		Camera::GetInstance()->SetTarget(this);
		mShaow = new Shadow();
		mShaow->Initialize(L"R_DashEffect", L"..\\Resource\\Animation\\BasicSkul\\R_DashEffect\\R_DashEffect.bmp");
		mShaow->SetTarget(this);
	}

	Player::~Player()
	{
		GameObject::~GameObject();
		delete mState;
		delete mShaow;
	}

	void Player::CompleteEvent()
	{
		Missile* missile = new Missile();
		missile->SetPos(this->GetPos());

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjectTile);
		info.Parameter2 = missile;

		EventManager::GetInstance()->EventPush(info);
	}

	void Player::Tick()
	{
		GameObject::Tick();
		mState->Tick();

		if (mShaow)
			mShaow->Tick();

	}

	void Player::Render(HDC hdc)
	{
		Vector2 pos = GetPos();
		Vector2 scale = GetScale();

		pos = Camera::GetInstance()->CalculatePos(pos);

		if (mShaow)
			mShaow->Render(hdc);

		GameObject::Render(hdc);

	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}
	void Player::ShadowEffect()
	{
	}
	void Player::SetState(eObjectState type)
	{
		mState->SetState(type);
	}
	eObjectState Player::GetState()
	{
		return mState->GetStateType();
	}
	eObjectState Player::GetPrevState()
	{
		return mState->GetPrevStateType();
	}
}
