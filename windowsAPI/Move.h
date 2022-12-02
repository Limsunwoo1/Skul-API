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

		eObjectState GetDirtion() {return mDirction; }
		void SetDirtion(eObjectState type);

		void SetAnimation();
		void NextState();
	private:
		eObjectState mDirction;
		std::wstring mCurAnimation;
	};
}