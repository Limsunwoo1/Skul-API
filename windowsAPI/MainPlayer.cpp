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
		BasicSkul* basicSkul = new BasicSkul();
		basicSkul->SetParentObject(basicSkul);

		SwordSkul* swordSkul = new SwordSkul();
		swordSkul->SetParentObject(swordSkul);

		this->SetPlayer(basicSkul);
		mNextPlayer = swordSkul;
		Camera::GetInstance()->SetTarget(basicSkul);
	}
	void MainPlayer::Tick()
	{
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			StateHandle* handle = mCurPlayer->GetStateHandle();
			ePlayerState type = handle->GetStateType();

			if (mNextPlayer != nullptr)
			{
				if (type != ePlayerState::SKILL_1
					&& type != ePlayerState::SKILL_2
					&& type != ePlayerState::SLIDING)
				{
					bool movetype = mCurPlayer->GetStateHandle()->
						GetState<Move>(ePlayerState::MOVE)->GetDirtion();

					mNextPlayer->GetStateHandle()->
						GetState<Move>(ePlayerState::MOVE)->SetDirtion(movetype);

					PlayerBase* temp = mCurPlayer;
					mCurPlayer = mNextPlayer;
					mNextPlayer = temp;

					mCurPlayer->SetState(ePlayerState::SWITCH);
					Reset();

					Camera::GetInstance()->SetTarget(mCurPlayer);
				}
			}
		}
		
		if (mCurPlayer)
			mCurPlayer->Tick();

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

		bool isground = false;
		if (mRigidbody)
		{
			isground = mRigidbody->GetGround();
			DeleteComponent<Rigidbody>();
		}
		mRigidbody = mCurPlayer->GetComponent<Rigidbody>();
		if (mRigidbody)
		{
			AddComponent(mRigidbody);
			mRigidbody->SetOwner(mCurPlayer);
			mRigidbody->SetGround(isground);
		}

		if(mNextPlayer != nullptr)
			mCurPlayer->SetPos(mNextPlayer->GetPos());
		//mCurPlayer->SetState(eObjectState::SWITCH);
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