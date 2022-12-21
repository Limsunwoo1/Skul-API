#include "MainPlayer.h"
#include "PlayerBase.h"
#include "BasicSkul.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "SwordSkul.h"
#include "Input.h"
#include "Camera.h"
#include "Move.h"
#include "StateHandle.h"
#include "SceneManager.h"
#include "Scene.h"

#include <iostream>

namespace sw
{
	MainPlayer::MainPlayer()
		: GameObject()
		, mCurPlayer(nullptr)
		, mNextPlayer(nullptr)
		, bPlayerSwitch(false)
	{
		Initialize();
	}
	MainPlayer::~MainPlayer()
	{
		DeleteComponent<Collider>();
		DeleteComponent<Rigidbody>();

		if(mCurPlayer)
			delete mCurPlayer;
		if (mNextPlayer)
			delete mNextPlayer;
	}

	void MainPlayer::Initialize()
	{
		SetPos(Vector2(450.f, 800.f));
		BasicSkul* basicSkul = new BasicSkul();
		basicSkul->SetParentObject(basicSkul);
		basicSkul->SetPos(GetPos());
		SwordSkul* swordSkul = new SwordSkul();
		swordSkul->SetParentObject(swordSkul);
		swordSkul->SetPos(GetPos());

		this->SetPlayer(basicSkul);
		mNextPlayer = swordSkul;
		Camera::GetInstance()->SetTarget(basicSkul);
	}
	void MainPlayer::Tick()
	{
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			KEY_DOWN_SPACE();
		}

		if (mCurPlayer)
			mCurPlayer->Tick();

		SetPos(mCurPlayer->GetPos());
		CheckGround();
	}
	void MainPlayer::Render(HDC hdc)
	{
		if (mCurPlayer)
			mCurPlayer->Render(hdc);
	}
	void MainPlayer::OnCollisionEnter(Collider* other)
	{
		if (mCurPlayer)
			mCurPlayer->OnCollisionEnter(other);
	}
	void MainPlayer::OnCollisionStay(Collider* other)
	{
		if (mCurPlayer)
			mCurPlayer->OnCollisionStay(other);
	}
	void MainPlayer::OnCollisionExit(Collider* other)
	{
		if (mCurPlayer)
			mCurPlayer->OnCollisionExit(other);
	}

	void MainPlayer::CheckGround()
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

			if (objPos.x + (objScale.x * 0.5f) < CPos.x - (CScale.x * 0.5f)
				|| objPos.x - (objScale.x * 0.5f) > CPos.x + (CScale.x * 0.5f))
				rigid->SetGround(false);
		}
	}

	void MainPlayer::KEY_DOWN_SPACE()
	{
		StateHandle* handle = mCurPlayer->GetStateHandle();
		ePlayerState type = handle->GetStateType();

		if (mNextPlayer != nullptr)
		{
			if (type != ePlayerState::SKILL_1
				&& type != ePlayerState::SKILL_2
				&& type != ePlayerState::SLIDING
				&& type != ePlayerState::SWITCH)
			{
				bool movetype = mCurPlayer->GetStateHandle()->
					GetState<Move>(ePlayerState::MOVE)->GetDirtion();

				mNextPlayer->GetStateHandle()->
					GetState<Move>(ePlayerState::MOVE)->SetDirtion(movetype);
				mCurPlayer->SetColliderBox(Box(Vector2::Zero, Vector2::Zero));
				PlayerBase* temp = mCurPlayer;
				mCurPlayer = mNextPlayer;
				mNextPlayer = temp;

				mCurPlayer->SetState(ePlayerState::SWITCH);
				Reset();
				
				Camera::GetInstance()->SetTarget(mCurPlayer);
			}
		}
	}

	void MainPlayer::Reset()
	{
		//mCurPlayer->SetPos(GetPos());
		DeleteComponent<Collider>();
		mCollider = mCurPlayer->GetComponent<Collider>();
		if (mCollider)
		{
			AddComponent(mCollider);
			mCollider->SetOwner(mCurPlayer);
		}

		if (mRigidbody)
			DeleteComponent<Rigidbody>();

		mRigidbody = mCurPlayer->GetComponent<Rigidbody>();
		if (mRigidbody)
		{
			AddComponent(mRigidbody);
			mRigidbody->SetOwner(mCurPlayer);
			mRigidbody->SetGround(false);
		}

		if(mNextPlayer != nullptr)
			mCurPlayer->SetPos(mNextPlayer->GetPos());
	}

	void MainPlayer::SwitchPlayer()
	{
		if (mNextPlayer == nullptr)
			return;

		PlayerBase* temp = mCurPlayer;
		mCurPlayer = mNextPlayer;
		mNextPlayer = temp;

		mCurPlayer->SetParentObject(this);
		Reset();
	}

	void MainPlayer::SetPlayer(PlayerBase* player)
	{
		mCurPlayer = player;
		mCurPlayer->SetParentObject(this);
		Reset();
	}
}