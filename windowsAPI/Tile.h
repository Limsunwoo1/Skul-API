#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class Tile : public GameObject
	{
	public:

		Tile(Vector2 pos);
		virtual ~Tile();

		void Initialize(Image* atlas, int index);
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetIndex(UINT index);
		UINT GetIndex() { return mIndex; }

	private:
		Image* mAtlas;

		UINT mIndex;
		UINT mX;
		UINT mY;
	};
}

