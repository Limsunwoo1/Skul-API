#include "Ground.h"
#include "PlayerBase.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Camera.h"
#include "Time.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StateHandle.h"
#include "Move.h"
#include "MainPlayer.h"
#include "MonsterBase.h"
#include "BossMonster.h"

#include <iostream>
#define FREEZMAX 2

namespace sw
{
	Ground::Ground()
		: type(eColliderLayer::Ground)
		, bTopBottomCollide(false)
		, mPlayerColCount(0)
		, mDelta(0.0f)
		, bPlayerDirction(true)
		, bCheckFreez(false)
		, mPlayer(nullptr)
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(400.f, 50.f));
		collider->SetOwner(this);
	}
	Ground::~Ground()
	{
	}
	void Ground::Tick()
	{
		GameObject::Tick();

		// 코드 정리하기
		//if (mPlayer != nullptr)
		//{
		//	Collider* pCol = mPlayer->GetComponent<Collider>();
		//	Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();
		//	Vector2 pPos = pCol->GetPos();
		//	Vector2 pScale = pCol->GetScale();

		//	Vector2 mPos = GetPos();
		//	Vector2 mScale = GetScale();

		//	if (mPos.y - (mScale.y * 0.5f) > pPos.y + (pScale.y * 0.5f)
		//		|| mPos.y + (mScale.y * 0.5f) < pPos.y - (pScale.y * 0.5f))
		//	{
		//		rigidbody->SetFreez(false);
		//		mPlayer = nullptr;
		//		bCheckFreez = false;
		//		mPlayerColCount = 0;
		//	}
		//}

		//if (bCheckFreez)
		//{
		//	// player rigidbody freez;
		//	if(mPlayer != nullptr)
		//	{
		//		StateHandle* state = mPlayer->GetStateHandle();
		//		Move* move = state->GetState<Move>(ePlayerState::MOVE);
		//		if (move->GetDirtion() != bPlayerDirction)
		//		{
		//			Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();
		//			rigidbody->SetFreez(false);
		//			bCheckFreez = false;
		//			mPlayerColCount = 0;
		//			mPlayer = nullptr;
		//		}
		//	}
		//}
		

		//mDelta += Time::GetInstance()->DeltaTime();
		//if (mDelta > 1.0f)
		//{
		//	mPlayerColCount = 0;
		//	mDelta -= 1.0f;
		//}
		//else
		//{
		//	if (mPlayerColCount > FREEZMAX)
		//	{
		//		// player rigidbody freez;

		//		if(mPlayer != nullptr)
		//		{
		//			Rigidbody* rigidbody = mPlayer->GetComponent<Rigidbody>();
		//			//rigidbody->SetFreez(true);

		//			StateHandle* state = mPlayer->GetStateHandle();
		//			Move* move = state->GetState<Move>(ePlayerState::MOVE);
		//			bPlayerDirction = move->GetDirtion();
		//		}
		//		mPlayerColCount = 0;
		//		bCheckFreez = true;
		//	}
		//}
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();

		CheckCollider(other);
	}

	void Ground::CheckCollider(Collider* other)
	{
		GameObject* object = other->GetOwner();
		Rigidbody* rigidbody = object->GetComponent<Rigidbody>();
		Vector2 pPos = other->GetPos();
		Vector2 pSca = other->GetScale();

		bool ground = rigidbody->GetGround();

		Vector2 mCPos = GetComponent<Collider>()->GetPos();
		Vector2 mCScale = GetComponent<Collider>()->GetScale();
		SetAngle();
		float angle = mAngle;
		

		if (mCPos.x < pPos.x)
		{
			Vector2 Vec1 = Vector2::Zero;
			Vector2 Vec2 = Vector2::Zero;
			if (mCPos.y < pPos.y)
			{
				// 오브젝트 좌상단
				Vec1 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y - (mCScale.y * 0.5f))).Normalize();
				Vec2 = Vector2(mCPos.x - (pPos.x - (pSca.x * 0.5f)), mCPos.y - (pPos.y - (pSca.y * 0.5f))).Normalize();
			}
			else if (mCPos.y > pPos.y)
			{
				// 오브젝트 좌하단
				Vec1 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y + (mCScale.y * 0.5f))).Normalize();
				Vec2 = Vector2(mCPos.x - (pPos.x - (pSca.x * 0.5f)), mCPos.y - (pPos.y + (pSca.y * 0.5f))).Normalize();
			}

			float that = ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
			float radian = acos(that);
			float inangle = UtilMath::ToDegree(radian);

			if (inangle < angle)
			{
				// 오른쪽 충돌
				float fLen = fabs(other->GetPos().x - GetComponent<Collider>()->GetPos().x);
				float fScale = (other->GetScale().x / 2.0f) + (GetComponent<Collider>()->GetScale().x / 2.0f);

				pPos.x += (fScale - fLen) + 1.0f;
				object->SetPos(pPos);
				other->SetPos(pPos);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);

				MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
				if (monster)
				{
					monster->SetHold(true);
					if (!monster->GetDirction() && monster->GetTarget() == nullptr)
						monster->SetDirction(true);
				}
			}
			else
				Top_Bottom_Collider(other);
		}
		else if (mCPos.x > pPos.x)
		{
			Vector2 Vec1 = Vector2::Zero;
			Vector2 Vec2 = Vector2::Zero;
			if (mCPos.y < pPos.y)
			{
				// 오브젝트 우상단
				Vec1 = Vector2(mCPos.x - (mCPos.x - (mCScale.x * 0.5f)), mCPos.y - (mCPos.y - (mCScale.y * 0.5f))).Normalize();
				Vec2 = Vector2(mCPos.x - (pPos.x + (pSca.x * 0.5f)), mCPos.y - (pPos.y - (pSca.y * 0.5f))).Normalize();
			}
			else if (mCPos.y > pPos.y)
			{
				// 오브젝트 우하단
				Vec1 = Vector2(mCPos.x - (mCPos.x - (mCScale.x * 0.5f)), mCPos.y - (mCPos.y + (mCScale.y * 0.5f))).Normalize();
				Vec2 = Vector2(mCPos.x - (pPos.x + (pSca.x * 0.5f)), mCPos.y - (pPos.y + (pSca.y * 0.5f))).Normalize();
			}

			float that = ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
			float radian = acos(that);
			float inangle = UtilMath::ToDegree(radian);

			if (inangle < angle)
			{
				// 왼쪽충돌
				float fLen = fabs(other->GetPos().x - GetComponent<Collider>()->GetPos().x);
				float fScale = (other->GetScale().x / 2.0f) + (GetComponent<Collider>()->GetScale().x / 2.0f);

				pPos.x -= (fScale - fLen) + 1.0f;
				object->SetPos(pPos);
				other->SetPos(pPos);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);

				MonsterBase* monster = dynamic_cast<MonsterBase*>(object);
				if (monster)
				{
					monster->SetHold(true);
					if (monster->GetDirction() && monster->GetTarget() == nullptr)
						monster->SetDirction(false);
				}
			}
			else
				Top_Bottom_Collider(other);
		}
	}

	void Ground::Top_Bottom_Collider(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
		Vector2 mCPos = GetComponent<Collider>()->GetPos();

		//float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fLen = fabs(GetComponent<Collider>()->GetScale().y * 0.5f);
		float fScale = (other->GetScale().y * 0.5f);
		float fY = GetComponent<Collider>()->GetPos().y;
		
		Vector2 playerPos = playerObj->GetPos();
		if (playerPos.y < mCPos.y)
		{
			//playerPos.y -= (fScale - fLen);
			playerPos.y = (fY - fLen - fScale);
			playerObj->SetPos(playerPos);
			rigidbody->SetGround(true);
		}
		else
		{
			Vector2 velo = rigidbody->GetVelocity();
			velo.y = 0;
			rigidbody->SetVelocity(velo);
			//playerPos.y += (fScale - fLen);
			playerPos.y = (fY + fLen + fScale);
			playerObj->SetPos(playerPos);

			rigidbody->SetGround(false);

			bTopBottomCollide = true;
		}
	}

	void Ground::SetAngle()
	{
		float angle;
		Vector2 mCPos = this->GetComponent<Collider>()->GetPos();
		Vector2 mCScale = this->GetComponent<Collider>()->GetScale();

		Vector2 Vec1 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y - (mCScale.y * 0.5f))).Normalize();
		Vector2 Vec2 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y + (mCScale.y * 0.5f))).Normalize();

		float that = ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
		float radian = acos(that);
		angle = UtilMath::ToDegree(radian);
		mAngle = angle;
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
		Rigidbody* rigidbody = other->GetOwner()->GetComponent<Rigidbody>();
		if (bTopBottomCollide)
			rigidbody->SetGround(false);

		bTopBottomCollide = false;
	}
}
