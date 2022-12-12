#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "Collider.h"
#include "Rigidbody.h"

namespace sw
{
	Tile::Tile(Vector2 pos)
		: GameObject(pos)
		, mAtlas(nullptr)
		, mY(-1)
		, mX(-1)
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetScale(Vector2(TILE_SIZE * TILE_SCALE -2, TILE_SIZE * TILE_SCALE -2));
		collider->SetOwner(this);
	}

	Tile::~Tile()
	{

	}

	void Tile::Initialize(Image* atlas, int index)
	{
		if (atlas == nullptr || index < 0)
			return;

		mAtlas = atlas;
		SetIndex(index);
	}

	void Tile::Tick()
	{
		GameObject::Tick();
	}

	void Tile::Render(HDC hdc)
	{
		if (mAtlas == nullptr)
			return;

		Vector2 ve = GetPos();
		Vector2 renderPos = Camera::GetInstance()->CalculatePos(ve);
		
		int tileImagY = mY * TILE_SIZE;
		int tileImagX = mX * TILE_SIZE;

		TransparentBlt(hdc
			, renderPos.x - (TILE_SIZE * TILE_SCALE * 0.5f), renderPos.y - (TILE_SIZE * TILE_SCALE * 0.5f)
			, TILE_SIZE * TILE_SCALE, TILE_SIZE * TILE_SCALE
			, mAtlas->GetDC()
			, tileImagX, tileImagY
			, TILE_SIZE, TILE_SIZE
			, RGB(255, 0, 255));

		GameObject::Render(hdc);
	}

	void Tile::SetIndex(UINT index)
	{
		if (!mAtlas)
			return;

		mIndex = index;

		int maxColumn = mAtlas->GetWidth() / TILE_SIZE;
		int maxRow = mAtlas->GetHeight() / TILE_SIZE;

		mY = index / maxColumn;
		mX = index % maxColumn;
	}
	void Tile::OnCollisionEnter(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
		rigidbody->SetGround(true);

		CheckCollider(other);
	}
	void Tile::OnCollisionStay(Collider* other)
	{

	}
	void Tile::OnCollisionExit(Collider* other)
	{

	}


	void Tile::CheckCollider(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
		Vector2 pPos = other->GetPos();
		Vector2 pSca = other->GetScale();

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

				pPos.x += (fScale - fLen) + 2.0f;
				playerObj->SetPos(pPos);
				rigidbody->SetGround(false);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);
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

				float a = fScale - fLen;
				pPos.x -= (fScale - fLen) + 2.0f;
				playerObj->SetPos(pPos);
				rigidbody->SetGround(false);

				Vector2 velo = rigidbody->GetVelocity();
				velo.x = 0;
				rigidbody->SetVelocity(velo);
			}
			else
				Top_Bottom_Collider(other);
		}
	}

	void Tile::Top_Bottom_Collider(Collider* other)
	{
		GameObject* playerObj = other->GetOwner();
		Vector2 mCPos = GetComponent<Collider>()->GetPos();

		float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
		float fScale = (other->GetScale().y / 2.0f) + (GetComponent<Collider>()->GetScale().y / 2.0f);

		Vector2 playerPos = playerObj->GetPos();
		if (playerPos.y < mCPos.y)
		{
			playerPos.y -= (fScale - fLen) + 2.0f;
			playerObj->SetPos(playerPos);
		}
		else if (playerPos.y > mCPos.y)
		{
			Rigidbody* rigidbody = playerObj->GetComponent<Rigidbody>();
			rigidbody->SetGround(false);

			Vector2 velo = rigidbody->GetVelocity();
			velo.y = 0;
			rigidbody->SetVelocity(velo);
			playerPos.y += (fScale - fLen) + 2.0f;
			playerObj->SetPos(playerPos);
		}
	}

	void Tile::SetAngle()
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

}