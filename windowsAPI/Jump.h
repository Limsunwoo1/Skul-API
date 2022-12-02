#pragma once
#include "State.h"

namespace sw
{
	class Jump: public State
	{
	public:
		Jump();
		~Jump();

		virtual void Start(PlayerBase* target)  override;
		virtual void Run() override;
		virtual void End() override;

		UINT GetJumpCount() { return mJumpCount; }
		void SetJumpCount(UINT count) { mJumpCount = count; }

		void SetStartAnimation();
		void PresseInput();
		void DownInput();
		void ChangeDrop();
	private:
		UINT mJumpCount;
	};
}

