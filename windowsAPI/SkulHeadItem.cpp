#include "SkulHeadItem.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Input.h"
#include "MainPlayer.h"
#include "PlayerBase.h"
#include "ObjectManager.h"
#include "BasicSkul.h"
#include "SwordSkul.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "samurai.h"

namespace sw
{
	SkulHeadItem::SkulHeadItem()
	{
		Initialize();
	}

	SkulHeadItem::~SkulHeadItem()
	{
	}

	void SkulHeadItem::Initialize()
	{
		SetScale(4.f, 4.f);
		// 애니메이터
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);
		animator->CreatAnimations(L"SowrdSkulHead", L"..\\Resource\\Animation\\HeadUi\\SwordSkulHeadItem",Vector2(0.f, 10.f));
		animator->CreatAnimations(L"SamuraiHead", L"..\\Resource\\Animation\\HeadUi\\SamuraiHeadItem",Vector2(0.f, 10.f));

		animator->Play(L"SowrdSkulHead");
		// 리지드바디
		Rigidbody* rigidbody =AddComponent<Rigidbody>();
		rigidbody->SetOwner(this);
		rigidbody->SetGround(false);
		rigidbody->SetVelocity(Vector2(0.f, -700.f));

		// 콜리더
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(40.f, 40.f);
	}

	void SkulHeadItem::Tick()
	{
		if (mHeadType == eSkulHead::Sword)
		{
			GetComponent<Animator>()->Play(L"SowrdSkulHead");
		}
		if (mHeadType == eSkulHead::Samurai)
		{
			GetComponent<Animator>()->Play(L"SamuraiHead");
		}
		GameObject::Tick();
	}

	void SkulHeadItem::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void SkulHeadItem::OnCollisionEnter(Collider* other)
	{
	}

	void SkulHeadItem::OnCollisionStay(Collider* other)
	{
		if (!GetComponent<Rigidbody>()->GetGround())
			return;

		if (KEY_DOWN(eKeyCode::F))
		{
			switch (mHeadType)
			{
			case eSkulHead::Basic:
			{
				
			}
			break;
			case eSkulHead::Sword:
			{
				SwordSkul* sword = new SwordSkul();
				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ObjectManager::GetInstance()->DeleteObject(scene);

				ObjectManager::GetInstance()->GetPlayer()->SetPlayer(sword);
				ObjectManager::GetInstance()->AddObject(scene);

				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::Item);
				info.Parameter2 = this;

				EventManager::GetInstance()->EventPush(info);
				other->OnCollisionExit(GetComponent<Collider>());
			}
			break;
			case eSkulHead::Samurai:
			{
				Samurai* samurai = new Samurai();
				Scene* scene = SceneManager::GetInstance()->GetPlayScene();
				ObjectManager::GetInstance()->DeleteObject(scene);

				ObjectManager::GetInstance()->GetPlayer()->SetPlayer(samurai);
				ObjectManager::GetInstance()->AddObject(scene);

				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::Item);
				info.Parameter2 = this;

				EventManager::GetInstance()->EventPush(info);
				other->OnCollisionExit(GetComponent<Collider>());
			}
			break;
			}
		}
	}

	void SkulHeadItem::OnCollisionExit(Collider* other)
	{
	}
}
