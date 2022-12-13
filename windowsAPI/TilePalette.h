#pragma once
#include "Common.h"

namespace sw
{
	class Tile;
	class Image;
	class Ground;
	class GameObject;
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
		void CreatTilePalette(const std::wstring& name, const std::wstring& path);
		void CreatGround(Vector2 pos, Vector2 scale, bool load = false);
		void DeleteGround();

		bool GetMode() { return mMode; }
		const Vector2& GetCurPos() const { return mGroundPos; }
		const Vector2& GetCurScale() const { return mGroundScale; }
		//void CreateTile
		//void CreateTiles

		void Save();
		void Load();
		void Load(const std::wstring& path);

		Image* GetAtlasImage() {return mImage;}

	private:
		Image* mImage;
		std::unordered_map<UINT64, Tile*> mTiles;
		std::unordered_map<UINT64, Ground*> mGround;
		std::stack<UINT64> mGroundKey;

		Ground* mPushObject;
		Ground* mPrevObject;
		Vector2 mGroundPos;
		Vector2 mGroundScale;

		bool mMode;
		bool bObserver;
	};
}

