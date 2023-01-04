#include "PlayerBase.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "EventManager.h"
#include "ObjectManager.h"

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
#include "Path.h"


namespace sw
{
	PlayerBase::PlayerBase()
		: mSlidingDirction(true)
		, mHeadImage(nullptr)
		, mSkilAImage(nullptr)
		, mSkilBImage(nullptr)
	{
		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			mSkils.push_back(new ObjectProjecTile());
		}
	}

	PlayerBase::~PlayerBase()
	{
		if (mHeadImage)
			delete mHeadImage;
		if (mSkilAImage)
			delete mSkilAImage;
		if (mSkilBImage)
			delete mSkilBImage;

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			delete mSkils[i];
		}
		mSkils.clear();

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
		EffectObject* effect = ObjectManager::GetInstance()->GetEffectObject();
		Animator* animator = effect->GetComponent<Animator>();
		effect->SetPos(GetPos());
		effect->SetScale(Vector2(5.0f, 5.0f));

		if (dirction)
			animator->Play(R_SKUL_DASHSMOKE);
		else
			animator->Play(L_SKUL_DASHSMOKE);

		animator->SetAlpha(255);

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::EFFECT);
		info.Parameter2 = effect;

		EventManager::GetInstance()->EventPush(info);
	}

	void PlayerBase::JumpSmoke()
	{
		EffectObject* effect = ObjectManager::GetInstance()->GetEffectObject();
		Animator* animator = effect->GetComponent<Animator>();
		effect->SetPos(GetPos());
		effect->SetScale(Vector2(1.0f, 1.0f));

		animator->Play(SKUL_JUMPSMOKE);
		animator->SetAlpha(255);

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::EFFECT);
		info.Parameter2 = effect;

		EventManager::GetInstance()->EventPush(info);
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
