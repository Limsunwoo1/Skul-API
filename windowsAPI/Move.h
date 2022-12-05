#pragma once
#include "State.h"

namespace sw
{
	class Move : public State
	{
	public:
		Move();
		~Move();

		virtual void Start(PlayerBase* target)  override;
		virtual void Run() override;
		virtual void End() override;

		bool GetDirtion() {return mDirction; }
		void SetDirtion(bool dirction);

		void SetAnimation();
		void NextState();
	private:
		bool mDirction;
		std::wstring mCurAnimation;
	};
}