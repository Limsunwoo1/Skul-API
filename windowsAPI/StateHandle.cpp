#include "StateHandle.h"
#include "State.h"
#include "Idle.h"
#include "Move.h"
#include "Jump.h"
#include "Attack.h"
#include "Sliding.h"
#include "Drop.h"

namespace sw
{
	StateHandle::StateHandle()
		: mTarget (nullptr)
	{
		
	}

	StateHandle::~StateHandle()
	{
		auto iter = mStates.begin();

		for (; iter != mStates.end();++iter)
		{
			if (iter->second == nullptr)
				continue;

			delete iter->second;
			iter->second = nullptr;
		}
		mStates.clear();
	}

	void StateHandle::Tick()
	{
		if (mCurState.second)
			mCurState.second->Run();
	}

	void StateHandle::SetState(eObjectState type)
	{
		std::map<eObjectState, State*>::iterator iter = mStates.find(type);
		if (iter == mStates.end())
			return;

		mPrevState.first = mCurState.first;
		mPrevState.second = mCurState.second;

		mCurState.first = iter->first;
		mCurState.second = iter->second;

		mCurState.second->Start(mTarget);
	}

	void StateHandle::PushState(eObjectState type, State* Instate)
	{
		Instate->SetTarget(mTarget);
		mStates.insert(std::make_pair(type, Instate));
	}


}