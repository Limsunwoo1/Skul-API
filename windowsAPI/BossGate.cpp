#include "BossGate.h"
#include "Collider.h"
#include "Animator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Input.h"
#include "EventManager.h"

namespace sw
{
	BossGate::BossGate()
		: GateObject()
	{
		Initialize();
	}
	BossGate::~BossGate()
	{
	}

	void BossGate::Tick()
	{
		GameObject::Tick();

		int a = SceneManager::GetInstance()->GetMonsterCount();
		if (SceneManager::GetInstance()->GetMonsterCount() <= 0)
		{
			SetDeactiveate(false);
		}

		if (!GetDeactivate())
		{
			if (GetComponent<Animator>()->GetCurAnimationName() != L"Activate")
			{
				SetScale(5.0f, 5.0f);
				GetComponent<Animator>()->Play(L"Activate", true);
			}
		}
	}

	void BossGate::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void BossGate::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);

		animator->CreatAnimations(L"Deactivate", L"..\\Resource\\Animation\\Gate\\Deactivate", Vector2(0.f, 50.f));
		animator->CreatAnimations(L"Activate", L"..\\Resource\\Animation\\Gate\\Activate", Vector2(0.f, 50.f));
		animator->CreatAnimations(L"BossActivate", L"..\\Resource\\Animation\\Gate\\BossGate", Vector2(0.f, 50.f));

		animator->Play(L"Deactivate");

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(100.f, 200.f);
	}

	void BossGate::OnCollisionEnter(Collider* other)
	{
		if (GetDeactivate())
			return;
	}

	void BossGate::OnCollisionStay(Collider* other)
	{
		if (GetDeactivate())
			return;

		if (KEY_DOWN(eKeyCode::F))
		{
			EventInfo info;
			info.Type = EventType::ChangeScene;
			info.Parameter1 = new eSceneType(mNextScene);

			EventManager::GetInstance()->EventPush(info);
		}
	}

	void BossGate::OnCollisionExit(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
}