#pragma once
#include "GameObject.h"

namespace sw
{
	class GateObject : public GameObject
	{
	public:
		GateObject();
		~GateObject();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize()override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		void SetDeactiveate(bool active) { mbDeactivate = active; }
		bool GetDeactivate() { return mbDeactivate; }

		void SetNextScene(eSceneType type) {mNextScene = type;}

		bool GetBossGate() { return mBossGate; }
		void SetBossGate(bool gate) { mBossGate = gate; }
	protected:
		UINT mMonsterCount;
		bool mbDeactivate;
		bool mBossGate;
		eSceneType mNextScene;
	};
}

