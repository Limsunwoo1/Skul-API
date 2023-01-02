#include "Tile.h"
#include "Image.h"
#include "Camera.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "SceneManager.h"

namespace sw
{
	Tile::Tile(Vector2 pos)
		: GameObject(pos)
		, mAtlas(nullptr)
		, mY(-1)
		, mX(-1)
		, type(eColliderLayer::Tile)
	{

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

	}

	void Tile::Render(HDC hdc)
	{
		if (IsDeath())
			return;

		if (mAtlas == nullptr)
			return;


		Vector2 ve = GetPos();
		Vector2 renderPos = Camera::GetInstance()->CalculatePos(ve);

		int tileImagY = mY * TILE_SIZE;
		int tileImagX = mX * TILE_SIZE;

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 255;

		TransparentBlt(hdc, renderPos.x - ((TILE_SIZE * TILE_SCALE) * 0.5f), renderPos.y - ((TILE_SIZE * TILE_SCALE) * 0.5f),
			TILE_SIZE * TILE_SCALE, TILE_SIZE * TILE_SCALE
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
}