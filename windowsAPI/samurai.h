#pragma once
#include "PlayerBase.h"
#include "GenericAnimator.h"

namespace sw
{
	class StaticObject;
	class Samurai : public PlayerBase
	{
	public:
		Samurai();
		virtual ~Samurai();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

		virtual void InitAnimtion() override;
		virtual void InitState() override;
		virtual void InitAttackCollider() override;
		virtual void InitSkils() override;

		virtual void OnAttackEffect(GameObject* other) override;

		virtual void SwitchProjecTile(GameObject* object) override;
		virtual void SkilAProjecTile(GameObject* object) override;
		virtual void SkilBProjecTile(GameObject* object) override;
		virtual void OnSkilB() override;
		virtual void InitMyObject() override;
		virtual void DeleteMyobject() override;
		virtual void InitMyObject(Scene* scene) override;
		virtual void DeleteMyobject(Scene* scene) override;

		void SkillAStart();
		void SkillAMoonStart();
		void SkillAMoonEnd();
		void SkillASetProjecTile();

		void SwitchStart();
		void SwitchProjecTileOn();
	private:
		Vector2 mArrivalPos;
		StaticObject* mBaldoBackGround;
		StaticObject* mBaldoMoon;

		GenericAnimator MyGenericAnimator;

		float mbaldo;
		float mbaldoRun;

		bool mAProjecTileOn;
		bool mSwitchProejcTileOn;
		bool mSKillAHitSound;
		bool mBaldo;
	};
}


