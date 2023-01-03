#include "AxeMonster.h"
#include "Animator.h"
#include "Path.h"
#include "Collider.h"
#include "ObjectProjecTile.h"
#include "EventManager.h"
#include "Rigidbody.h"
namespace sw
{
	AxeMonster::AxeMonster()
		: MonsterBase()
	{
		SetHp(50);
		SetPower(2);
		InitializeAnimation();
		InitalizeCollider();
		InitializeBox();

		SetScale(Vector2(5.f, 5.f));
		mAttackX = 300;
		mAttackY = 200;
		mArmer = true;

		mAttackCooltimeMax = 3.0f;

		Vector2 colscale = GetComponent<Collider>()->GetScale();
		mHpPanel->SetPos(Vector2(GetPos().x, GetPos().y - (colscale.y * 0.5f)));
		mHpPanel->SetSize(Vector2(GetHp() * 5.f, 15.f));
		mHpBar->SetSize(Vector2(GetHp() * 5.f, 8.f));

		// SkilInit
		for (int i = 0; i < 4; ++i)
		{
			mProjecTile.push_back(new ObjectProjecTile());
			mProjecTile[i]->SetTarget(this);
			mProjecTile[i]->SetReuse_Time(0.8f);
			mProjecTile[i]->SetEffectName(L"AxeMonster_AttackEft");
			mProjecTile[i]->SetEvent(std::bind(&AxeMonster::SkilAttack, this, std::placeholders::_1));
			Animator* animator = mProjecTile[i]->GetComponent<Animator>();
			animator->CreatAnimations(L"AxeMonster_AttackEft", 
				L"..\\Resource\\Animation\\MonsterAttackEffect\\AxeMonster",
				Vector2(0.f,50.f), 0.05);
			Collider* collider = mProjecTile[i]->GetComponent<Collider>();
			collider->SetScale(Vector2(120.f, 250.f));
		}
	}
	AxeMonster::~AxeMonster()
	{
		GameObject::~GameObject();
		for (int i = 0; i < 4; ++i)
		{
			delete mProjecTile[i];
		}
		mProjecTile.clear();
	}

	void AxeMonster::Tick()
	{
		MonsterBase::Tick();

		for (int i = 0; i < mProjecTile.size(); ++i)
		{
			Animator* animator = mProjecTile[i]->GetComponent<Animator>();
			if (animator->bPlayAnimation() && animator->isComplete())
			{
				mProjecTile[i]->SetDeath(true);

				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjecTile);
				info.Parameter2 = mProjecTile[i];

				EventManager::GetInstance()->EventPush(info);
			}
		}
	}

	void AxeMonster::InitializeAnimation()
	{
		RName = L"R_AxeMonster";
		LName = L"L_AxeMonster";

		mAnimator = AddComponent<Animator>();
		mAnimator->SetOwner(this);

		mAnimator->CreatAnimations(RName + L"Idle", AXEMONSTER_R_PATH(L"Idle"), Vector2(0.0f, 10.f), 0.1f);
		mAnimator->CreatAnimations(LName + L"Idle", AXEMONSTER_L_PATH(L"Idle"), Vector2(0.0f, 10.f), 0.1f);

		mAnimator->CreatAnimations(RName + L"Move", AXEMONSTER_R_PATH(L"Move"), Vector2(0.f, 30.f), 0.2f);
		mAnimator->CreatAnimations(LName + L"Move", AXEMONSTER_L_PATH(L"Move"), Vector2(0.f, 30.f), 0.2f);

		mAnimator->CreatAnimations(RName + L"Attack", AXEMONSTER_R_PATH(L"Attack"), Vector2(0.f, 30.f), 0.3f);
		mAnimator->CreatAnimations(LName + L"Attack", AXEMONSTER_L_PATH(L"Attack"), Vector2(0.f, 30.f), 0.3f);

		mAnimator->Play(RName + L"Idle", true);

		mAnimator->PushImageEvent(RName + L"Attack", 9, std::bind(&AxeMonster::OnSkilAttack, this));
		mAnimator->PushImageEvent(LName + L"Attack", 9, std::bind(&AxeMonster::OnSkilAttack, this));
	}

	void AxeMonster::InitializeBox()
	{
		mStaringCollider.BoxOffset = Vector2(0.0f, -30.f);
		mStaringCollider.BoxScale = Vector2(400.f, 200.f);

		mAttackcollider.BoxOffset = Vector2(0.0f, -30.f);
		mAttackcollider.BoxScale = Vector2(200.f, 200.f);
	}
	void AxeMonster::InitalizeCollider()
	{
		Collider* collider = AddComponent<Collider>();
		collider->SetOwner(this);
		collider->SetScale(Vector2(250.f, 180.f));
	}
	void AxeMonster::Hit()
	{
		// hp °¨¼Ò
	}

	void AxeMonster::ProejcTielDelte()
	{
		for (int i = 0; i < 4; ++i)
		{
			EventInfo info;
			info.Type = EventType::DeleteObject;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjecTile);
			info.Parameter2 = mProjecTile[i];
			EventManager::GetInstance()->EventPush(info);
		}
		mProjecTile.clear();
	}

	void AxeMonster::OnSkilAttack()
	{
		int a = 0;
		float offset = 0.0f;

		for (int i = 0; i < mProjecTile.size(); i++)
		{
			if (mDirction)
				a += 200;
			else
				a -= 200;

			mProjecTile[i]->SetDeath(false);
			mProjecTile[i]->SetOffset(Vector2(a, 10));
			mProjecTile[i]->SetScale(Vector2(4.0f,4.0f));
			mProjecTile[i]->GetComponent<Animator>()->Play(mProjecTile[i]->GetEffectName());
			mProjecTile[i]->SetStartOffset(offset);
			offset += 0.2;

			EventInfo info;
			info.Type = EventType::AddObejct;
			info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjecTile);
			info.Parameter2 = mProjecTile[i];

			EventManager::GetInstance()->EventPush(info);
		}
	}
	void AxeMonster::SkilAttack(GameObject* other)
	{
		Rigidbody* rigidbody = other->GetComponent<Rigidbody>();
		Vector2 velo = rigidbody->GetVelocity();
		velo.y -= 500.f;
		rigidbody->SetVelocity(velo);
		rigidbody->SetGround(false);
		if (mDirction)
			rigidbody->AddForce(Vector2(8000.f, 0.0f));
		else
			rigidbody->AddForce(Vector2(-8000.f, 0.0f));
	}
}
