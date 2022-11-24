#include "TilePalette.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Tile.h"
#include "Scene.h"
#include "ToolScene.h"
#include "Input.h"
#include <commdlg.h>
#include "def.h"

namespace sw
{
	TilePalette::TilePalette()
		: bObserver(false)
	{
		mImage = ResourceManager::GetInstance()->
			Load<Image>(L"TileAtlas", L"..\\Resource\\Image\\Tile.bmp");
	}

	TilePalette::~TilePalette()
	{

	}

	void TilePalette::TileObserver()
	{
		std::unordered_map<UINT64, Tile*>::iterator iter;
		iter = mTiles.begin();

		for (; iter != mTiles.end();)
		{
			if (iter->second == nullptr)
			{
				iter = mTiles.erase(iter);
				continue;
			}
			++iter;
		}
	}

	void TilePalette::Tick()
	{
		if (bObserver)
			TileObserver();

		if (KEY_PRESSE(eKeyCode::LBTN))
		{
			if (GetFocus())
			{
				Vector2 mousePos = Input::GetInstance()->GetMousePos();

				int x = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int y = mousePos.y / (TILE_SIZE * TILE_SCALE);

				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ToolScene* toolscene = dynamic_cast<ToolScene*>(scene);
				UINT index = toolscene->GetTileIndex();

				CreateTile(index, Vector2(x, y));
			}
		}
		else if (KEY_PRESSE(eKeyCode::RBTN))
		{
			if (GetFocus())
			{
				Vector2 mousePos = Input::GetInstance()->GetMousePos();

				int x = mousePos.x / (TILE_SIZE * TILE_SCALE);
				int y = mousePos.y / (TILE_SIZE * TILE_SCALE);

				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ToolScene* toolscene = dynamic_cast<ToolScene*>(scene);
				UINT index = toolscene->GetTileIndex();

				DeleteTile(mousePos);
			}
		}
	}

	void TilePalette::Render(HDC hdc)
	{

	}

	void TilePalette::CreateTile(UINT index, Vector2 indexPos)
	{
		TileID key(indexPos.x, indexPos.y);
		key.ID;

		std::unordered_map<UINT64, Tile*>::iterator iter;
		iter = mTiles.find(key.ID);

		if (iter != mTiles.end())
		{
			// ÇöÀç Å¸ÀÏ index ·Î ¹Ù²ãÁÜ
			if(iter->second != nullptr)
				iter->second->SetIndex(index);

			return;
		}

		Vector2 objectPos = indexPos * (TILE_SIZE * TILE_SCALE);
		Tile* tile = new Tile(objectPos);
		tile->Initialize(mImage, index);

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Tile);
		info.Parameter2 = tile;

		EventManager::GetInstance()->EventPush(info);

		mTiles.insert(std::make_pair(key.ID, tile));
	}

	void TilePalette::DeleteTile(Vector2 mousePos)
	{
		std::unordered_map<UINT64, Tile*>::iterator iter;

		for (iter = mTiles.begin();iter != mTiles.end(); ++iter)
		{
			Vector2 iterPos = iter->second->GetPos();
			Vector2 iterScale = iter->second->GetScale();

			if (iterPos.x > mousePos.x || iterPos.x + (TILE_SIZE * TILE_SCALE) < mousePos.x)
				continue;

			if (iterPos.y > mousePos.y || iterPos.y + (TILE_SIZE * TILE_SCALE) < mousePos.y)
				continue;

			if (iter->second == nullptr)
				return;

			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Tile);
			info.Parameter2 = iter->second;

			EventManager::GetInstance()->EventPush(info);

			iter->second = nullptr;
			bObserver = true;
		}
	}

	void TilePalette::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");
		if (pFile == nullptr)
			return;

		std::unordered_map<UINT64, Tile*>::iterator iter = mTiles.begin();
		for (; iter != mTiles.end(); ++iter)
		{
			int tileIndex = (*iter).second->GetIndex();
			fwrite(&tileIndex, sizeof(int), 1, pFile);

			TileID id;
			id.ID = (*iter).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);
		}

		fclose(pFile);
	}

	void TilePalette::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");
		if (pFile == nullptr)
			return;

		while (true)
		{
			int tileIndex = 0;
			TileID id;

			if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
				break;

			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
				break;

			CreateTile(tileIndex, Vector2(id.left, id.right));
		}

		fclose(pFile);
	}

	void TilePalette::Load(const std::wstring& path)
	{
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, path.c_str(), L"rb");
		if (pFile == nullptr)
			return;

		while (true)
		{
			int tileIndex = 0;
			TileID id;

			if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
				break;

			if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
				break;

			CreateTile(tileIndex, Vector2(id.left, id.right));
		}

		fclose(pFile);
	}
}