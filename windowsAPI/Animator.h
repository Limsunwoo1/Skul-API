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
		struct Event
		{
			void operator =(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};
		struct Events
		{
			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};
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

		Animation* FindAnimation(const std::wstring name);
		bool bPlayAnimation();
		bool isComplete() { return mPlayAnimation->isComplete(); }

		Events* FindEvents(const std::wstring key);
		std::function<void()>& GetStartEvent(const std::wstring key);
		std::function<void()>& GetCompleteEvent(const std::wstring key);
		std::function<void()>& GetEndEvent(const std::wstring key);

	private:
		std::map<const std::wstring, Animation*> mAnimations;
		std::map<const std::wstring, Events*> mEvents;

		Animation* mPlayAnimation;
		Image* mSpriteSheet;

		bool mbLoop;
	};
}

