#include "Item.h"
#include "Collider.h"
#include "Animator.h"
#include "SkulHeadItem.h"
#include "SwordSkul.h"
#include "EventManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Scene.h"

namespace sw
{
	Item::Item()
		: mMonsterCount(0)
		, mbDeactivate(true)
	{
		SetScale(4.0f, 4.0f);
		Initialize();
	}
	Item::~Item()
	{
	}
	void Item::Tick()
	{
		GameObject::Tick();

		if (SceneManager::GetInstance()->GetMonsterCount() <= 0)
		{
			SetDeactiveate(false);
		}
	}
	void Item::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Item::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);

		animator->CreatAnimations(L"HeadItem", L"..\\Resource\\Animation\\Gate\\HeadItem");

		animator->Play(L"HeadItem");

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(200.f, 100.f);
	}

	void Item::OnCollisionEnter(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
	void Item::OnCollisionStay(Collider* other)
	{
		if (GetDeactivate())
			return;

		if (KEY_DOWN(eKeyCode::F))
		{
			sw::DropHead.Play(false);

			eSkulHead hd = GetHeadType();
			SkulHeadItem* item = new SkulHeadItem();
			item->SetPos(GetPos());
			item->SetSkulHeadType(GetHeadType());
			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Item);
			info.Parameter2 = item;

			EventManager::GetInstance()->EventPush(info);

			EventInfo info2;
			info2.Type = EventType::DeleteObject;
			info2.Parameter1 = new eColliderLayer(eColliderLayer::Gate);
			info2.Parameter2 = this;

			EventManager::GetInstance()->EventPush(info2);

			SceneManager::GetInstance()->GetPlayScene()->SetSceneChange(true);
			other->OnCollisionExit(GetComponent<Collider>());
		}
	}
	void Item::OnCollisionExit(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
}