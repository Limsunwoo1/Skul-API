#include "TilePalette.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Image.h"
#include "Tile.h"
#include "ToolScene.h"
#include "Input.h"
#include <commdlg.h>
#include "def.h"
#include "Camera.h"
#include "Ground.h"
#include "Collider.h"

namespace sw
{
	TilePalette::TilePalette()
		: bObserver(false)
		, mMode(true)
		, mPushObject(nullptr)
		, mPrevObject(nullptr)
		, mGroundPos(Vector2::Zero)
		, mGroundScale(Vector2::Zero)
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
		// Y 가 0 or 1 일때 예외처리추가
		int Y = fileCount / TILE_LINE_X;
		if ((fileCount % TILE_LINE_X) < 0)
			++Y;

		mImage = Image::Create(name, width * TILE_LINE_X, height * Y);
		int size = images.size();
		
		int Xindex = 0;
		int Yindex = 0;
		for (Image* image : images)
		{
			BitBlt(mImage->GetDC(), width * Xindex, height * Yindex, image->GetWidth(), image->GetHeight(),
				image->GetDC(), 0, 0, SRCCOPY);

			Xindex++;
			if (Xindex >= TILE_LINE_X)
			{
				Xindex = 0;
				Yindex++;
			}
		}
	}

	void TilePalette::Tick()
	{
		mGround;
		mGroundKey;
		mTiles;
		if (bObserver)
			TileObserver();

		if (KEY_DOWN(eKeyCode::NUM_0))
		{
			if (mMode)
				mMode = false;
			else
				mMode = true;
		}

		if (mMode)
		{
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
					mousePos += Camera::GetInstance()->GetDistance();

					int x = mousePos.x / (TILE_SIZE * TILE_SCALE);
					int y = mousePos.y / (TILE_SIZE * TILE_SCALE);
					
					Scene* scene = SceneManager::GetInstance()->GetPlayScene();
					ToolScene* toolscene = dynamic_cast<ToolScene*>(scene);
					UINT index = toolscene->GetTileIndex();

					DeleteTile(mousePos);
				}
			}
		}
		else
		{
			if (KEY_UP(eKeyCode::LBTN))
			{
				CreatGround(mGroundPos, mGroundScale);
			}
			else if (KEY_DOWN(eKeyCode::LBTN))
			{
				if (GetFocus())
				{
					Vector2 mousePos = Input::GetInstance()->GetMousePos();
					mousePos += Camera::GetInstance()->GetDistance();

					if(mGroundPos == Vector2::Zero)
						mGroundPos = mousePos;
				}
			}
			else if (KEY_PRESSE(eKeyCode::LBTN))
			{
				if (GetFocus())
				{
					Vector2 mousePos = Input::GetInstance()->GetMousePos();
					mousePos += Camera::GetInstance()->GetDistance();

					mGroundScale = Vector2(mousePos.x - mGroundPos.x, mousePos.y - mGroundPos.y);
				}
			}
			else if (KEY_DOWN(eKeyCode::RBTN))
			{
				if (GetFocus())
				{
					DeleteGround();
				}
			}
		}
	}

	void TilePalette::Render(HDC hdc)
	{

	}

	void TilePalette::CreatGround(Vector2 pos, Vector2 scale, bool load)
	{
		if (pos == Vector2::Zero)
			return;

		if (scale == Vector2::Zero)
			return;

		Ground* ground = nullptr;
		ColliderID key;
		if (load)
		{
			ground = new Ground();
			ground->SetPos(Vector2(pos.x , pos.y));
			ground->SetScale(scale);

			key.left = pos.x;
			key.right = pos.y;
			key.ID;

			Collider* col = ground->GetComponent<Collider>();
			col->SetPos(Vector2(pos.x , pos.y));
			col->SetScale(scale);
			col->SetOwner(ground);
		}
		else
		{
			ground = new Ground();
			ground->SetPos(Vector2(pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f)));
			ground->SetScale(scale);

			key.left = pos.x + (scale.x * 0.5f);
			key.right = pos.y + (scale.y * 0.5f);
			key.ID;

			Collider* col = ground->GetComponent<Collider>();
			col->SetPos(Vector2(pos.x + (scale.x * 0.5f), pos.y + (scale.y * 0.5f)));
			col->SetScale(scale);
			col->SetOwner(ground);
		}

		if (ground == nullptr)
			return;

		EventInfo info;
		info.Type = EventType::AddObejct;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Ground);
		info.Parameter2 = ground;
		
		EventManager::GetInstance()->EventPush(info);

		mGround.insert(std::make_pair(key.ID, ground));
		mGroundKey.push(key.ID);

		mGroundPos = Vector2::Zero;
		mGroundScale = Vector2::Zero;
	}

	void TilePalette::DeleteGround()
	{
		if (mGroundKey.empty())
			return;

		std::unordered_map<UINT64, Ground*>::iterator iter;
		ColliderID key;
		key.ID = mGroundKey.top();
		iter = mGround.find(key.ID);

		if (iter == mGround.end())
			return;

		EventInfo info;
		info.Type = EventType::DeleteObject;
		info.Parameter1 = new eColliderLayer(eColliderLayer::Ground);
		info.Parameter2 = iter->second;
		EventManager::GetInstance()->EventPush(info);

		mGround.erase(iter);
		mGroundKey.pop();
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

		Vector2 objectPos;
		objectPos.x = (indexPos.x * (TILE_SIZE * TILE_SCALE)) + ((TILE_SIZE * TILE_SCALE) * 0.5f);
		objectPos.y = indexPos.y * (TILE_SIZE * TILE_SCALE) + ((TILE_SIZE * TILE_SCALE) * 0.5f);
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

			if (iterPos.x + ((TILE_SIZE * TILE_SCALE) * 0.5f) < mousePos.x 
				|| iterPos.x - ((TILE_SIZE * TILE_SCALE) * 0.5f) > mousePos.x)
				continue;

			if (iterPos.y + ((TILE_SIZE * TILE_SCALE) * 0.5f) < mousePos.y 
				|| iterPos.y - ((TILE_SIZE * TILE_SCALE) * 0.5f) > mousePos.y)
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
			UINT32 type = (UINT32)(*iter).second->GetLayer();
			fwrite(&type, sizeof(UINT32), 1, pFile);

			int tileIndex = (*iter).second->GetIndex();
			fwrite(&tileIndex, sizeof(int), 1, pFile);

			TileID id;
			id.ID = (*iter).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);
		}

		std::unordered_map<UINT64, Ground*>::iterator iterator = mGround.begin();
		for (; iterator != mGround.end(); ++iterator)
		{
			UINT32 type = (UINT32)(*iterator).second->GetLayer();
			fwrite(&type, sizeof(UINT32), 1, pFile);

			TileID id;
			id.ID = (*iterator).first;
			fwrite(&id.ID, sizeof(UINT64), 1, pFile);

			Vector2 scale = (*iterator).second->GetScale();
			TileID keyscale(scale.x, scale.y);
			fwrite(&keyscale.ID, sizeof(UINT64), 1, pFile);
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
			UINT32 type;

			int tileIndex = 0;
			TileID id;
			ColliderID pos;
			ColliderID scale;

			if (fread(&type, sizeof(UINT32), 1, pFile) == NULL)
				break;

			if (type == (UINT32)eColliderLayer::Ground)
			{
				if (fread(&pos, sizeof(UINT64), 1, pFile) == NULL)
					break;

				if (fread(&scale, sizeof(UINT64), 1, pFile) == NULL)
					break;

				CreatGround(Vector2(pos.left, pos.right), Vector2(scale.left, scale.right),true);
			}
			else if (type == (UINT32)eColliderLayer::Tile)
			{
				if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
					break;

				if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
					break;

				CreateTile(tileIndex, Vector2(id.left, id.right));
			}
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
			UINT32 type;

			int tileIndex = 0;
			TileID id;
			ColliderID pos;
			ColliderID scale;

			if (fread(&type, sizeof(UINT32), 1, pFile) == NULL)
				break;

			if (type == (UINT32)eColliderLayer::Ground)
			{
				if (fread(&pos, sizeof(UINT64), 1, pFile) == NULL)
					break;

				if (fread(&scale, sizeof(UINT64), 1, pFile) == NULL)
					break;

				CreatGround(Vector2(pos.left, pos.right), Vector2(scale.left, scale.right), true);
			}
			else if (type == (UINT32)eColliderLayer::Tile)
			{
				if (fread(&tileIndex, sizeof(int), 1, pFile) == NULL)
					break;

				if (fread(&id.ID, sizeof(UINT64), 1, pFile) == NULL)
					break;

				CreateTile(tileIndex, Vector2(id.left, id.right));
			}
		}

		fclose(pFile);
	}
}