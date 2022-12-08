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
		bool CheckCurScen(eSceneType type) { if (mPlayScene == mScenes[(int)type]) return true; return false; }
	private:
		Scene* mScenes[(UINT)eSceneType::Max];
		Scene* mPlayScene;
	};
}
