#include "Ground.h"
#include "PlayerBase.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "UtilMath.h"


namespace sw
{
	Ground::Ground()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(8000.f, 50.f));
		collider->SetOwner(this);
	}
	Ground::~Ground()
	{
	}
	void Ground::Tick()
	{
		GameObject::Tick();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
		rigidbody->SetGround(true);

		Vector2 pPos = other->GetPos();
		Vector2 pSca = other->GetScale();

		Vector2 mCPos = GetComponent<Collider>()->GetPos();
		Vector2 mCScale = GetComponent<Collider>()->GetScale();
		
		float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fScale = (other->GetScale().y / 2.0f) + (GetComponent<Collider>()->GetScale().y / 2.0f);


		// 백터의 내적을 이용하여 옆면 충돌도 체크
		/*if (fLen < fScale)
		{
			Vector2 playerPos = playerObj->GetPos();
			if (playerPos.y < mCPos.y)
			{
				playerPos.y -= (fScale - fLen) + 1.0f;
				playerObj->SetPos(playerPos);
			}
			else if (playerPos.y > mCPos.y)
			{
				Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
				rigidbody->SetGround(false);

				Vector2 velo = rigidbody->GetVelocity();
				velo.y = 0;
				rigidbody->SetVelocity(velo);
				playerPos.y += (fScale - fLen) + 1.0f;
				playerObj->SetPos(playerPos);
			}
		}*/

		// 내적
		Vector2 CollisionDirection = pPos - mCPos;
		float Length = CollisionDirection.Length();

		Vector2 test;
		test.x = (mCPos.x - (mCScale.x * 0.5f)) - (mCPos.x + (mCScale.x * 0.5f));
		test.y = 0;
		float Length2 = test.Length();

		float that = (CollisionDirection.x * test.x) + (CollisionDirection.y * test.y);
		float Radian = acos(that / (Length * Length2));

		float Dgree = UtilMath::ToDegree(Radian);

		// 삼각함수
		Vector2 ColliderLength;
		ColliderLength.x = (mCPos.x + (mCScale.x * 0.5f));
		ColliderLength.y = (mCPos.y - (mCScale.y * 0.5f));
		float CLength = ColliderLength.Length();

		float h = UtilMath::Cos(CLength / ColliderLength.x);
		float g = UtilMath::ToDegree(h);
		int a = 0;

		float angle;

		{		
			Vector2 Vec1 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y - (mCScale.y * 0.5f))).Normalize();
			Vector2 Vec2 = Vector2(mCPos.x - (mCPos.x + (mCScale.x * 0.5f)), mCPos.y - (mCPos.y + (mCScale.y * 0.5f))).Normalize();
	
			float that = ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
			float radian = acos(that);
			angle = UtilMath::ToDegree(radian);
		}

		if(mCPos.x < pPos.x)
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

				pPos.x += (fScale - fLen) + 1.0;
				playerObj->SetPos(pPos);
				rigidbody->SetGround(false);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);
			}
			else
			{
				Vector2 playerPos = playerObj->GetPos();
				if (playerPos.y < mCPos.y)
				{
					playerPos.y -= (fScale - fLen) + 1.0f;
					playerObj->SetPos(playerPos);
				}
				else if (playerPos.y > mCPos.y)
				{
					Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
					rigidbody->SetGround(false);

					Vector2 velo = rigidbody->GetVelocity();
					velo.y = 0;
					rigidbody->SetVelocity(velo);
					playerPos.y += (fScale - fLen) + 1.0f;
					playerObj->SetPos(playerPos);
				}
			}
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

				float a = fScale - fLen;
				pPos.x -= (fScale - fLen) + 1.0;
				playerObj->SetPos(pPos);
				rigidbody->SetGround(false);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);
			}
			else
			{
				Vector2 playerPos = playerObj->GetPos();
				if (playerPos.y < mCPos.y)
				{
					playerPos.y -= (fScale - fLen) + 1.0f;
					playerObj->SetPos(playerPos);
				}
				else if (playerPos.y > mCPos.y)
				{
					Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
					rigidbody->SetGround(false);

					Vector2 velo = rigidbody->GetVelocity();
					velo.y = 0;
					rigidbody->SetVelocity(velo);
					playerPos.y += (fScale - fLen) + 1.0f;
					playerObj->SetPos(playerPos);
				}
			}
		}	
	}

	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
		other->GetOwner()->GetComponent<Rigidbody>()->SetGround(false);
	}
}
