#pragma once
#include "Common.h"
#include "PlayerBase.h"

namespace sw
{
	class State
	{
	public:
		State();
		virtual ~State();

		virtual void Start(PlayerBase* target) = 0;
		virtual void Run() = 0;
		virtual void End() = 0;

		void SetTarget(PlayerBase* target) { mTarget = target; }
		PlayerBase* GetTarget() { return mTarget; }

		void SetR_Animation(std::wstring animation) { R_Animation = animation; }
		void SetL_Animation(std::wstring animation) { L_Animation = animation; }

		std::wstring GetR_Animation() { return R_Animation; }
		std::wstring GetL_Animation() { return L_Animation; }
	private:
		PlayerBase* mTarget;
		
		std::wstring R_Animation;
		std::wstring L_Animation;
	};
}

