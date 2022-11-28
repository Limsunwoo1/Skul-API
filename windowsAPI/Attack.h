#pragma once
#include "State.h"

namespace sw
{
	class Attack : public State
	{
	public:
		Attack();
		~Attack();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

		void SetStartAnimation();
		void SetAnimation();

		void SetAttackCount(UINT count) { mAttackCount = count; }

	private:
		std::vector<std::wstring> mR_AttackSequence;
		std::vector<std::wstring> mL_AttackSequence;

		UINT mAttackCount;
		float mDelta;
		bool bInput;
	};
}

