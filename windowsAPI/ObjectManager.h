#pragma once
#include "Common.h"

namespace sw
{
	class MainPlayer;
	class EffectObject;
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

		EffectObject* GetEffectObject();
		void PushEffectObject(EffectObject* object);

	private:
		MainPlayer* mPlayer;
		std::queue<EffectObject*> mEffects;
	};
}

