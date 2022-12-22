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
		Vector2 GetPos() { return mPos; }

		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetOffset() { return mOffset; }

		void SetScale(Vector2 scale) { mScale = scale; }
		Vector2 GetScale() { return mScale; }

	private:
		Image* mImage;
		PlayerBase* mTarget;

		Vector2 mPos;
		Vector2 mOffset;
		Vector2 mScale;
	};
}

