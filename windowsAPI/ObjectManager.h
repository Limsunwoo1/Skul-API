#pragma once
#include "Common.h"

namespace sw
{
	class MainPlayer;
	class EffectObject;
	class Scene;
	class ObjectManager
	{
		SINGLE(ObjectManager);
	public:
		void Initialize();
		void Release();

		MainPlayer* GetPlayer() { return mPlayer; }
		void SetPlayer(MainPlayer* player) { mPlayer = player; }

		void AddObject(eSceneType type);
		void AddObject(Scene* scene);
		void DeleteObject(eSceneType type);
		void DeleteObject(Scene* scene);

		EffectObject* GetEffectObject();
		void PushEffectObject(EffectObject* object);

	private:
		MainPlayer* mPlayer;
		std::queue<EffectObject*> mEffects;
	};
}

