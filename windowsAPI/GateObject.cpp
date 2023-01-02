#include "GateObject.h"
#include "Collider.h"
#include "Animator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Input.h"
#include "EventManager.h"

namespace sw
{
	GateObject::GateObject()
		: mMonsterCount(0)
		, mbDeactivate(true)
		, mBossGate(false)
		, mNextScene(eSceneType::End)
	{
		SetScale(4.0f, 4.0f);
		Initialize();
	}
	GateObject::~GateObject()
	{
	}

	void GateObject::Tick()
	{
		GameObject::Tick();

		int a = SceneManager::GetInstance()->GetMonsterCount();
		if (SceneManager::GetInstance()->GetMonsterCount() <= 0)
		{
			SetDeactiveate(false);
		}

		if (!GetDeactivate())
		{
			if (mBossGate)
			{
				if (GetComponent<Animator>()->GetCurAnimationName() != L"BossActivate")
				{
					GetComponent<Animator>()->Play(L"BossActivate", true);
					GetComponent<Collider>()->SetScale(100.f, 200.f);
					SetPos(GetPos().x, GetPos().y - 20);
					SetScale(6.0f, 6.0f);
				}
			}
			else if (GetComponent<Animator>()->GetCurAnimationName() != L"Activate")
			{
				SetScale(5.0f, 5.0f);
				GetComponent<Animator>()->Play(L"Activate",true);
			}
		}
	}

	void GateObject::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GateObject::Initialize()
	{
		Animator* animator = AddComponent<Animator>();
		animator->SetOwner(this);

		animator->CreatAnimations(L"Deactivate", L"..\\Resource\\Animation\\Gate\\Deactivate", Vector2(0.f, 50.f));
		animator->CreatAnimations(L"Activate", L"..\\Resource\\Animation\\Gate\\Activate",Vector2(0.f, 50.f));
		animator->CreatAnimations(L"BossActivate", L"..\\Resource\\Animation\\Gate\\BossGate", Vector2(0.f, 50.f));

		animator->Play(L"Deactivate");

		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(100.f, 200.f);
	}

	void GateObject::OnCollisionEnter(Collider* other)
	{
		if (GetDeactivate())
			return;
	}

	void GateObject::OnCollisionStay(Collider* other)
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

	void GateObject::OnCollisionExit(Collider* other)
	{
		if (GetDeactivate())
			return;
	}
}