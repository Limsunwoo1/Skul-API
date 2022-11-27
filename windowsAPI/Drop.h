#pragma once
#include "State.h"

namespace sw
{
	class Drop : public State
	{
	public:
		Drop();
		~Drop();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

		void SetAnimation();
		void SetStartAnimation();
		void NextStateInput();
	};
}