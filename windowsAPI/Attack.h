#pragma once
#include "State.h"

namespace sw
{
	class AttackCollider;
	class GameObject;
	class Attack : public State
	{
	public:
		Attack();
		~Attack();

		virtual void Start(PlayerBase* target)  override;
		virtual void Run() override;
		virtual void End() override;

		void AttackSound();
		void SetStartAnimation();
		void SetAnimation();
		void StartCollider();

		void SetAttackCount(UINT count) { mAttackCount = count; }

		void SetR_AttackSequence(std::wstring attack) { mR_AttackSequence.push_back(attack); }
		void SetL_AttackSequence(std::wstring attack) { mL_AttackSequence.push_back(attack); }

		Box GetCurBox() { return mColliderBox; }
		void SetSkul(eSkulHead type) { mSkul = type; }
	private:
		std::vector<std::wstring> mR_AttackSequence;
		std::vector<std::wstring> mL_AttackSequence;
		std::vector<GameObject*> mTemp;
		Box mColliderBox;
		eSkulHead mSkul;

		UINT mAttackCount;
		float mDelta;
		bool bInput;
	};
}

