#include "ObjectManager.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Effect.h"
#include "ObejctProjecTile.h"

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
			scene->AddGameObject(mPlayer->GetPlayer()->GetEffect(), eColliderLayer::EFFECT);
			scene->AddGameObject(mPlayer->GetPlayer()->GetProjecTile(), eColliderLayer::Player_ProjectTile);
		}

		if (mPlayer->GetNextPlayer() != nullptr)
		{
			scene->AddGameObject(mPlayer->GetNextPlayer()->GetEffect(), eColliderLayer::EFFECT);
			scene->AddGameObject(mPlayer->GetNextPlayer()->GetProjecTile(), eColliderLayer::Player_ProjectTile);
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
		scene->DeleteGameObject(mPlayer->GetPlayer()->GetEffect(), eColliderLayer::EFFECT);
		scene->DeleteGameObject(mPlayer->GetPlayer()->GetProjecTile(), eColliderLayer::Player_ProjectTile);

		scene->DeleteGameObject(mPlayer->GetNextPlayer()->GetEffect(), eColliderLayer::EFFECT);
		scene->DeleteGameObject(mPlayer->GetNextPlayer()->GetProjecTile(), eColliderLayer::Player_ProjectTile);
	}

}


