#pragma once
#include "Common.h"

namespace sw
{
	class Image;
	class PlayerBase;
	class Effect
	{
	public:
		Effect();
		~Effect();

		void Tick();
		void Render(HDC hdc);

		void SetImage(std::wstring key, std::wstring path);
		Image* GetImage() { return mImage; }

		void SetTarget(PlayerBase* target);
		PlayerBase* GetTarget() { return mTarget; }

		void SetPos(Vector2 pos) { mPos = pos; }

	private:
		Image* mImage;
		Vector2 mPos;
		PlayerBase* mTarget;
	};
}

