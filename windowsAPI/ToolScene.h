#pragma once
#include "Scene.h"
namespace sw
{
	class TilePalette;
	class Image;
	class ToolScene : public Scene
	{
	public:
		ToolScene();
		virtual ~ToolScene();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void Enter();
		virtual void Exit();
		
		void SaveTilePalette();
		void LoadTilePalette();
		void LoadTilePalette(const std::wstring& path);

		Image* GetAtlasImage();

		void SetTileIndex(UINT index) { mTileIndex = index;}
		UINT GetTileIndex() { return mTileIndex; }

		
	private:
		TilePalette* mTilePalette;
		UINT mTileIndex;
		bool mMode;
	};
}

