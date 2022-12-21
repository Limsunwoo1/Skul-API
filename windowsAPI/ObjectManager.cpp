#include "ObjectManager.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Effect.h"
#include "ObjectProjecTile.h"

namespace sw
{
	ObjectManager::ObjectManager()
	{

	}
	ObjectManager::~ObjectManager()
	{

	}

	void ObjectManager::Initialize()
	{
		mPlayer = new MainPlayer();
	}

	void ObjectManager::Release()
	{
		eSceneType type = SceneManager::GetInstance()->GetPlayeSceneType();
		DeleteObject(type);
		if (mPlayer)
			delete mPlayer;
	}

	void ObjectManager::AddObject(eSceneType type)
	{
		Scene* scene = SceneManager::GetInstance()->GetScene(type);
		if (!scene)
			return;
		if (!mPlayer)
			return;

		scene->AddGameObject(mPlayer, eColliderLayer::Player);
		if (mPlayer->GetPlayer() != nullptr)
		{
			PlayerBase* player = mPlayer->GetPlayer();
			EffectObject* effect = player->GetEffect();
			scene->AddGameObject((GameObject*)effect, eColliderLayer::EFFECT);

			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjectTile);
			}
		}

		if (mPlayer->GetNextPlayer() != nullptr)
		{
			PlayerBase* player = mPlayer->GetNextPlayer();
			EffectObject* effect = player->GetEffect();
			scene->AddGameObject((GameObject*)effect, eColliderLayer::EFFECT);
			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjectTile);
			}
		}
	}

	void ObjectManager::DeleteObject(eSceneType type)
	{
		Scene* scene = SceneManager::GetInstance()->GetScene(type);
		if (!scene)
			return;
		if (!mPlayer)
			return;

		EffectObject* effect1 = mPlayer->GetPlayer()->GetEffect();
		scene->DeleteGameObject(mPlayer, eColliderLayer::Player);
		scene->DeleteGameObject((GameObject*)effect1, eColliderLayer::EFFECT);

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjectTile);
		}

		EffectObject* effect2 = mPlayer->GetNextPlayer()->GetEffect();
		scene->DeleteGameObject((GameObject*)effect2, eColliderLayer::EFFECT);
		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetNextPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjectTile);
		}
	}

}


