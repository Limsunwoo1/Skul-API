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

		void SetState(ePlayerState type);
		ePlayerState GetStateType() { return mCurState.first; }
		ePlayerState GetPrevStateType() { return mPrevState.first; }
		void SetTarget(PlayerBase* target) { mTarget = target; }
		PlayerBase* GetTarget() { return mTarget; }

		void PushState(ePlayerState type, State* state);

		template<typename T>
		T* GetState(ePlayerState type)
		{
			std::map<ePlayerState, State*>::iterator iter = mStates.find(type);
			if (iter == mStates.end())
				return nullptr;

			return dynamic_cast<T*>(iter->second);
		}

	private:
		PlayerBase* mTarget;
		
		std::map<ePlayerState, State*> mStates;

		std::pair<ePlayerState, State*> mCurState;
		std::pair<ePlayerState, State*> mPrevState;
	};
}

