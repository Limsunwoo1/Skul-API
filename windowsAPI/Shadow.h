#pragma once
#include "Common.h"

namespace sw
{
	class Player;
	class Effect;
	class Shadow
	{
	public:
		Shadow();
		~Shadow();

		void Initialize(const std::wstring key, const std::wstring path);
		void Render(HDC hdc);

		Player* GetTarget() { return mTarget; }
		void SetTarget(Player* target);

	private:
		float mDuraction;
		UINT mShdowMax;
		UINT mCurEffect;

		Player* mTarget;
		std::vector<Effect*> mShadows;
	};
}

