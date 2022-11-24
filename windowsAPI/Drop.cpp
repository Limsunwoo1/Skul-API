#include "Drop.h"
#include "Rigidbody.h"
#include "Input.h"
#include "StateHandle.h"
#include "Move.h"


namespace sw
{
	Drop::Drop()
	{
	}
	Drop::~Drop()
	{
	}
	void Drop::Start(Player* target)
	{
		SetTarget(target);
	}
	void Drop::Run()
	{
		Player* player = GetTarget();
		Rigidbody* rigidbody = player->GetComponent<Rigidbody>();
		StateHandle* stathandle = player->GetStateHandle();

		if (rigidbody->GetGround())
		{
			End();
			player->SetState(eObjectState::IDLE);
			return;
		}

		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			stathandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::LEFT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(-300.f, 0.0f));
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			stathandle->GetState<Move>(eObjectState::LEFT)->SetDirtion(eObjectState::RIGHT);
			player->GetComponent<Rigidbody>()->AddForce(Vector2(300.f, 0.0f));
		}
	}
	void Drop::End()
	{

	}
}