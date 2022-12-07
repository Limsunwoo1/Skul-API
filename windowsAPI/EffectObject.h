#pragma once
#include "GameObject.h"

namespace sw
{
	class Animator;
	class EffectObject : public GameObject
	{
	public:
		EffectObject();
		~EffectObject();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() const { return mName; }

		void SetOffset(Vector2 offset) { mOffset = offset; }
		Vector2 GetOffset() { return mOffset; }

	private:
		std::wstring mName;
		Vector2 mOffset;

		Animator* mAnimator;
	};
}

