#pragma once
#include "State.h"

namespace sw
{
	class Move : public State
	{
	public:
		Move();
		~Move();

		virtual void Start(Player* target)  override;
		virtual void Run() override;
		virtual void End() override;

		eObjectState GetDirtion() {return mDirtion; }
		void SetDirtion(eObjectState type);
	private:
		eObjectState mDirtion;
		std::wstring mCurAnimation;
	};
}