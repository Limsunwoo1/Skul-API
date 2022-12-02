#pragma once
#include "Common.h"

namespace sw
{
	class State;
	class PlayerBase;
	class StateHandle
	{
	public:
		StateHandle();
		~StateHandle();

		void Tick();

		void SetState(eObjectState type);
		eObjectState GetStateType() { return mCurState.first; }
		eObjectState GetPrevStateType() { return mPrevState.first; }
		void SetTarget(PlayerBase* target) { mTarget = target; }
		PlayerBase* GetTarget() { return mTarget; }

		void PushState(eObjectState type, State* state);

		template<typename T>
		T* GetState(eObjectState type)
		{
			std::map<eObjectState, State*>::iterator iter = mStates.find(type);
			if (iter == mStates.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

	private:
		PlayerBase* mTarget;
		
		std::map<eObjectState, State*> mStates;

		std::pair<eObjectState, State*> mCurState;
		std::pair<eObjectState, State*> mPrevState;
	};
}

