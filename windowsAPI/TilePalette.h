#pragma once
#include "Common.h"

namespace sw
{
	class Tile;
	class Image;
	class TilePalette
	{
	public:
		TilePalette();
		~TilePalette();

		void Tick();
		void Render(HDC hdc);

		void CreateTile(UINT index, Vector2 indexPos);
		void DeleteTile(Vector2 mousePos);

		void TileObserver();
		//void CreateTile
		//void CreateTiles

		void Save();
		void Load();
		void Load(const std::wstring& path);

		Image* GetAtlasImage() {return mImage;}

	private:
		Image* mImage;
		std::unordered_map<UINT64, Tile*> mTiles;

		bool bObserver;
	};
}

