#pragma once
#include "Component.h"
#include "Animation.h"

namespace sw
{
	class Animation;
	class Image;
	class Animator : public Component
	{
	public:
		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void Play(const std::wstring name, bool bLoop = false);

		void CreateAnimation(const std::wstring name, Image* image
			, Vector2 leftTop, Vector2 Size, Vector2 offset
			, UINT spriteLegth, float duration, bool bAffectedCamera = true);

		void CreatAnimations(const std::wstring& name, const std::wstring& path
			, Vector2 offset = Vector2::Zero
			, float duration = 0.1);

		std::wstring CreateAniamtionKey(std::wstring path);

		Animation::Event& StartEvent() {return mPlayAnimation->StartEvent();}
		Animation::Event& CompleteEvent() { return mPlayAnimation->CompleteEvent(); }
		Animation::Event& EndEvent() { return mPlayAnimation->EndEvent(); }

		bool bPlayAnimation();

	private:
		Animation* FindAnimation(const std::wstring name);

	private:
		std::map<const std::wstring, Animation*> mAnimations;
		Animation* mPlayAnimation;
		Image* mSpriteSheet;

		bool mbLoop;
	};
}

