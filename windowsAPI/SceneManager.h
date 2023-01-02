#pragma once
#include "Common.h"


namespace sw
{
	class Scene;

	class SceneManager
	{
		SINGLE(SceneManager);

	public:
		void Initalize();
		void Tick();
		void Render(HDC hdc);
		void Release();

		void ChangeScene(eSceneType type);

		Scene* GetPlayScene() { return mPlayScene; }
		Scene* GetScene(eSceneType type) { return mScenes[(UINT)type]; }
		eSceneType GetPlayeSceneType();
		bool CheckCurScen(eSceneType type) { if (mPlayScene == mScenes[(int)type]) return true; return false; }
		void LoadTileMap(const std::wstring& path);

		void SetMonsterCount();
		UINT GetMonsterCount() { return mMonsterCount; }
		void ClearObject();
	private:
		Scene* mScenes[(UINT)eSceneType::Max];
		Scene* mPlayScene;

		UINT mMonsterCount;
	};
}
