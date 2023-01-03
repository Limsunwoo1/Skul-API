#include "ObjectManager.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EffectObject.h"
#include "ObjectProjecTile.h"
#include "UIManager.h"

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
		UIManager::GetInstance()->DeleteUi(eUIType::Character);
		UIManager::GetInstance()->DeleteUi(eUIType::Character_MainHead);
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
			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
			}
		}

		if (mPlayer->GetNextPlayer() != nullptr)
		{
			PlayerBase* player = mPlayer->GetNextPlayer();
			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
			}
		}
	}

	void ObjectManager::AddObject(Scene* scene)
	{
		if (!scene)
			return;
		if (!mPlayer)
			return;

		scene->AddGameObject(mPlayer, eColliderLayer::Player);

		if (mPlayer->GetPlayer() != nullptr)
		{
			PlayerBase* player = mPlayer->GetPlayer();
			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
			}
		}

		if (mPlayer->GetNextPlayer() != nullptr)
		{
			PlayerBase* player = mPlayer->GetNextPlayer();
			for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
			{
				scene->AddGameObject(player->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
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

		scene->DeleteGameObject(mPlayer, eColliderLayer::Player);

		if(mPlayer->GetPlayer() == nullptr)
			return;

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
		}

		if (mPlayer->GetNextPlayer() == nullptr)
			return;

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetNextPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
		}
	}

	void ObjectManager::DeleteObject(Scene* scene)
	{
		if (!scene)
			return;
		if (!mPlayer)
			return;

		scene->DeleteGameObject(mPlayer, eColliderLayer::Player);

		if (mPlayer->GetPlayer() == nullptr)
			return;

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
		}

		if (mPlayer->GetNextPlayer() == nullptr)
			return;

		for (int i = (int)eSkilType::Switch; i < (int)eSkilType::End; ++i)
		{
			scene->DeleteGameObject(mPlayer->GetNextPlayer()->GetProjecTile((eSkilType)i), eColliderLayer::Player_ProjecTile);
		}
	}

	EffectObject* ObjectManager::GetEffectObject()
	{
		EffectObject* effect = nullptr;
		if (mEffects.empty())
		{
			effect = new EffectObject();
			effect->SetDeath(false);
			return effect;
		}

		effect = mEffects.front();
		mEffects.pop();
		effect->SetDeath(false);

		return effect;
	}

	void ObjectManager::PushEffectObject(EffectObject* object)
	{
		object->SetDeath(true);
		mEffects.push(object);
	}
}


