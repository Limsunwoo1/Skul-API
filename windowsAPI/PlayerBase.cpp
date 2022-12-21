#include "PlayerBase.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"
#include "EffectObject.h"

#include "Scene.h"
#include "Image.h"
#include "Animator.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "StateHandle.h"
#include "Shadow.h"

#include "EffectObject.h"
#include "ObjectProjecTile.h"
#include "Move.h"


namespace sw
{
	PlayerBase::PlayerBase()
	{
		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			mSkils.push_back(new ObjectProjecTile());
		}

		mEffect = new EffectObject();
		Animator* animator = mEffect->GetComponent<Animator>();

		animator->CreatAnimations(L"R_DashSmoke", L"..\\Resource\\Animation\\Effect\\R_DashSmoke", Vector2(65.f, 0.f), 0.1f);
		animator->CreatAnimations(L"L_DashSmoke", L"..\\Resource\\Animation\\Effect\\L_DashSmoke", Vector2(-65.f, 0.f), 0.1f);

		animator->CreatAnimations(L"JumpSmoke", L"..\\Resource\\Animation\\Effect\\JumpSmoke", Vector2(0.f, -40.f), 0.05f);
	}

	PlayerBase::~PlayerBase()
	{
		GameObject::~GameObject();
	}

	void PlayerBase::SetColliders(wstring key, Box box)
	{
		std::pair<std::wstring, Box> Inpiar;
		Inpiar.first = key;
		Inpiar.second = box;

		mColliders.push_back(Inpiar);
	}

	const Box& PlayerBase::GetColliders(wstring key) const
	{
		for (std::pair<std::wstring, Box> collider : mColliders)
		{
			if (collider.first == key)
				return collider.second;
		}

		return Box{Vector2::Zero, Vector2::Zero};
	}


	void PlayerBase::Tick()
	{
		GameObject::Tick();
	}

	void PlayerBase::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void PlayerBase::DashSmoke()
	{
		bool dirction = this->GetStateHandle()->GetState<Move>(ePlayerState::MOVE)->GetDirtion();
		Animator* animator = mEffect->GetComponent<Animator>();
		mEffect->SetDeath(false);
		mEffect->SetPos(GetPos());
		mEffect->SetScale(Vector2(5.0f, 5.0f));

		if (dirction)
			animator->Play(L"R_DashSmoke");
		else
			animator->Play(L"L_DashSmoke");

		animator->SetAlpha(255);
	}

	void PlayerBase::JumpSmoke()
	{
		Animator* animator = mEffect->GetComponent<Animator>();
		mEffect->SetDeath(false);
		
		mEffect->SetPos(GetPos());
		mEffect->SetScale(Vector2(1.0f, 1.0f));

		animator->Play(L"JumpSmoke");
		animator->SetAlpha(255);
	}

	void PlayerBase::SetState(ePlayerState type)
	{
		mState->SetState(type);
	}
	ePlayerState PlayerBase::GetState()
	{
		return mState->GetStateType();
	}
	ePlayerState PlayerBase::GetPrevState()
	{
		return mState->GetPrevStateType();
	}
}
