#include "StateHandle.h"
#include "State.h"
#include "Idle.h"
#include "Move.h"
#include "Jump.h"
#include "Sliding.h"
#include "Drop.h"

namespace sw
{

	StateHandle::StateHandle()
		: mTarget (nullptr)
	{
		Move* move = new Move();

		mStates.insert(std::make_pair(eObjectState::IDLE, new Idle));
		mStates.insert(std::make_pair(eObjectState::LEFT, move));
		mStates.insert(std::make_pair(eObjectState::RIGHT, move));
		mStates.insert(std::make_pair(eObjectState::JUMP, new Jump));
		mStates.insert(std::make_pair(eObjectState::SLIDING, new Sliding));
		mStates.insert(std::make_pair(eObjectState::DROP, new Drop));


	}

	StateHandle::~StateHandle()
	{

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


}