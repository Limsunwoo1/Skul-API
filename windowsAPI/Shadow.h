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

		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetOffset() { return mOffset; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

	private:
		float mDelta;
		UINT mShdowMax;
		UINT mCurEffect;
		Vector2 mOffset;
		Vector2 mScale;

		PlayerBase* mTarget;
		std::vector<Effect*> mShadows;
	};
}

