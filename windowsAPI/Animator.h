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
		struct ImageEvent
		{
			std::wstring	mName;
			UINT			mSheetNum;
			Event			mEvent;
			ImageEvent()
			{
				mName = L"";
				mSheetNum = 0;
				mEvent = nullptr;
			};
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

		void PushImageEvent(const std::wstring key, UINT sheetIndex, std::function<void()> fun);
		void SetAlpha(int alpha) { mAlpha = alpha; }
		int GetAlpha() { return mAlpha; }

		const std::wstring& GetCurAnimationName() const { return mCurAnimationName; }
		void SetCurAnimationName(const std::wstring& name) { mCurAnimationName = name; }
	private:
		void ImageEventCheck();
		void FindImageEvent(const std::wstring name);
	private:
		std::map<const std::wstring, Animation*> mAnimations;
		std::map<const std::wstring, Events*> mEvents;
		std::vector<ImageEvent*> mImageEvent;
		ImageEvent* mCurEvent;

		Animation* mPlayAnimation;
		Image* mSpriteSheet;
		std::wstring mCurAnimationName;
		int mAlpha;

		bool mbLoop;
		bool mEvent_Run;
	};
}

