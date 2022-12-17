#pragma once
#include "Common.h"

namespace sw
{
	class MainPlayer;
	class ObjectManager
	{
		SINGLE(ObjectManager);
	public:
		void Initialize();
		void Release();

		MainPlayer* GetPlayer() { return mPlayer; }
		void SetPlayer(MainPlayer* player) { mPlayer = player; }

		void AddObject(eSceneType type);
		void DeleteObject(eSceneType type);

	private:
		MainPlayer* mPlayer;
	};
}

