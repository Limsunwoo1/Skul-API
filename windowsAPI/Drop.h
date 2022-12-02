#pragma once
#include "State.h"

namespace sw
{
	class Drop : public State
	{
	public:
		Drop();
		~Drop();

		virtual void Start(PlayerBase* target)  override;
		virtual void Run() override;
		virtual void End() override;

		void SetAnimation();
		void SetStartAnimation();
		void NextStateInput();
	};
}