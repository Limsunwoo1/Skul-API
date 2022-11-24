#include "Tile.h"
#include "Image.h"
#include "Camera.h"

namespace sw
{
	Tile::Tile(Vector2 pos)
		: GameObject(pos)
		, mAtlas(nullptr)
		, mY(-1)
		, mX(-1)
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
		if (mAtlas == nullptr)
			return;

		Vector2 ve = GetPos();
		//Vector2 renderPos = Camera::GetInstance()->CalculatePos(GetPos());

		int tileImagY = mY * TILE_SIZE;
		int tileImagX = mX * TILE_SIZE;

		TransparentBlt(hdc
			, ve.x, ve.y
			, TILE_SIZE * TILE_SCALE, TILE_SIZE * TILE_SCALE
			, mAtlas->GetDC()
			, tileImagX, tileImagY
			, TILE_SIZE, TILE_SIZE
			, RGB(255, 0, 255));
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