#pragma once
#include "Common.h"

namespace sw
{
	class PlayerBase;
	class Effect;
	class Shadow
	{
	public:
		Shadow();
		~Shadow();

		void Initialize(const std::wstring key, const std::wstring path);
		void Tick();
		void Render(HDC hdc);

		PlayerBase* GetTarget() { return mTarget; }
		void SetTarget(PlayerBase* target);

	private:
		float mDelta;
		UINT mShdowMax;
		UINT mCurEffect;

		PlayerBase* mTarget;
		std::vector<Effect*> mShadows;
	};
}

