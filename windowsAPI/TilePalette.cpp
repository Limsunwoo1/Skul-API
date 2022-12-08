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
#include "Camera.h"

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

	void TilePalette::CreatTilePalette(const std::wstring& name, const std::wstring& path)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images;
		for (auto& file : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring cnt = std::to_wstring(fileCount);
			std::wstring filename = file.path().filename();
			std::wstring fullName = path + L"\\" + filename;
			Image* image = ResourceManager::GetInstance()->Load<Image>(filename, fullName);
			images.push_back(image);

			// 제일큰 리소스의 크기 셋팅
			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}
		// a 가 0 or 1 일때 예외처리추가
		int a = fileCount / 10;

		mImage = Image::Create(name, width * 10, height * a);
		int size = images.size();
		size = size / 10;
		if (size == 0 || size == 1)
			size = 1;
		

		int Xindex = 0;
		int Yindex = 0;
		for (Image* image : images)
		{
			BitBlt(mImage->GetDC(), width * Xindex, height * Yindex, image->GetWidth(), image->GetHeight(),
				image->GetDC(), 0, 0, SRCCOPY);

			Xindex++;
			if (Xindex >= 10)
			{
				Xindex = 0;
				Yindex++;
			}
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
				mousePos += Camera::GetInstance()->GetDistance();

				int x = (int)mousePos.x / (TILE_SIZE * TILE_SCALE);
				int y = (int)mousePos.y / (TILE_SIZE * TILE_SCALE);

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
			// 현재 타일 index 로 바꿔줌
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