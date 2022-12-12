#include "Rigidbody.h"
#include "Time.h"
#include "UtilMath.h"
#include "PlayerBase.h"
#include "MainPlayer.h"

namespace sw
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mFriction(400.f)
	{
		mLimitVelocity.x = 200.f;
		mLimitVelocity.y = 1000.f;

		mbGround = false;
		mGravity = Vector2(0.0f, 900.f);
	}

	Rigidbody::~Rigidbody()
	{

	}

	void Rigidbody::Tick()
	{
		// 이동
		// F = M x A
		// A = F / M
		mAccelation = mForce / mMass;

		// 속도에 가속도를 더한다
		//mVelocity += mAccelation * Time::GetInstance()->DeltaTime();

		if (mbGround)
		{
			// 땅위에 있을때
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = UtilMath::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			// 공중에 있을때
			mVelocity += mGravity * Time::GetInstance()->DeltaTime();
		}


		// 최대 속도 제한
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = UtilMath::Dot(mVelocity, gravity);
		gravity = gravity * dot;

		Vector2 sideVelocity = mVelocity - gravity;
		if (mLimitVelocity.y < gravity.Length())
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}

		if (mLimitVelocity.x < sideVelocity.Length())
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;

		// 마찰력 조건 (적용된 힘이 없고, 속도가 0 이 아닐때)
		//if (!(mVelocity == Vector2::Zero))
		//{
		//	// 속도 반대 방향으로 마찰력을 적용
		//	Vector2 friction = -mVelocity;
		//	friction = 
		//		friction.Normalize() * mFriction * mMass * Time::GetInstance()->DeltaTime();

		//	// 마찰력으로 인한 속도 감소량 현재 속도보다 더 큰 경우
		//	float mVelocityLength = mVelocity.Length();
		//	float frictionLength = friction.Length();
		//	if (mVelocityLength < frictionLength)
		//	{
		//		// 속도를 0 으로 만든다
		//		mVelocity = Vector2::Zero;
		//	}
		//	else
		//	{
		//		// 속도에서 마찰략으로 인한 반대방향으로 속도를 차감
		//		mVelocity += friction;
		//	}
		//}

		// 속도에 맞게 물체를 이동시킨다
		Vector2 pos = GetOwner()->GetPos();
		PlayerBase* player = dynamic_cast<PlayerBase*>(GetOwner());
		if (player != nullptr)
		{
			if(player->GetState() != ePlayerState::SLIDING)
			{
				if (!mbGround)
				{
					mVelocity = mVelocity + mGravity * Time::GetInstance()->DeltaTime();
					pos = pos + mVelocity * Time::GetInstance()->DeltaTime();
				}
			}
			else
			{

			}

			pos = pos + mForce * Time::GetInstance()->DeltaTime();
			player->SetPos(pos);
			mForce.clear();
			return;
		}
		else
		{
			if (!mbGround)
			{
				mVelocity = mVelocity + mGravity * Time::GetInstance()->DeltaTime();
				pos = pos + mVelocity * Time::GetInstance()->DeltaTime();
			}
		}


		pos = pos + mForce * Time::GetInstance()->DeltaTime();
		pos = pos + mVelocity * Time::GetInstance()->DeltaTime();
		GetOwner()->SetPos(pos);
		mForce.clear();
	}

	void Rigidbody::Render(HDC hdc)
	{

	}

	void Rigidbody::AddForce(Vector2 force)
	{
		mForce += force;
	}
}