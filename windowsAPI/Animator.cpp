#include "Animator.h"
#include "Image.h"
#include "ResourceManager.h"
#include "GameObject.h"

namespace sw
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mPlayAnimation(nullptr)
		, mbLoop(false)
		, mAlpha(255)
		, mEvent_Run(false)
	{

	}

	Animator::~Animator()
	{
		//std::map<std::wstring, Animation*> mAnimations;
		for (auto iter : mAnimations)
		{
			delete iter.second;
		}
		mAnimations.clear();
		//std::map<std::wstring, Events*> mEvents;
		for (auto iter : mEvents)
		{
			delete iter.second;
		}

		for (auto iter : mImageEvent)
		{
			delete iter;
		}

		mEvents.clear();
		mImageEvent.clear();
	}

	void Animator::Tick()
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->Tick();
			if (mEvent_Run)
				ImageEventCheck();

			if (mbLoop && mPlayAnimation->isComplete())
			{
				Animator::Events* events
					= FindEvents(mPlayAnimation->GetName());
				if (events != nullptr)
					events->mCompleteEvent();

				mPlayAnimation->Reset();
			}
		}
	}
	void Animator::Render(HDC hdc)
	{
		if (mPlayAnimation != nullptr)
		{
			mPlayAnimation->SetAlpha(mAlpha);
			mPlayAnimation->Render(hdc);
		}
	}

	std::wstring Animator::CreateAniamtionKey(std::wstring path)
	{
		std::wstring keyString = path;

		// 얘니메이션 폴더 이름 추룰
		UINT pos = keyString.find_last_of(L"\\");
		std::wstring tail = keyString.substr(pos + 1, keyString.length());
		keyString = keyString.substr(0, pos);

		// 애니메이션 오브젝트 이름 추출
		pos = keyString.find_last_of(L"\\");
		std::wstring head = keyString.substr(pos + 1, keyString.length());
		keyString = head + tail;

		return keyString;
	}

	Animation* Animator::FindAnimation(const std::wstring name)
	{
		std::map<const std::wstring, Animation*>::iterator iter
			= mAnimations.find(name);

		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}

	void Animator::CreateAnimation(const std::wstring name, Image* image
		, Vector2 leftTop, Vector2 Size, Vector2 offset, UINT spriteLegth
		, float duration, bool bAffectedCamera)
	{
		Animation* animation = FindAnimation(name);
		if (animation != nullptr)
		{
			int a = 0;
			return;
		}

		animation = new Animation();
		animation->Create(image, leftTop, Size, offset
			, spriteLegth, duration, bAffectedCamera);

		animation->SetName(name);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	//Sprte 이미지를 Animation 으로 만들어주는 함수
	void Animator::CreatAnimations(const std::wstring& name, const std::wstring& path
		, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;

		std::filesystem::path fs(path);
		std::vector<Image*> images;
		for (auto& file : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring cnt = std::to_wstring(fileCount);
			std::wstring filename = file.path().filename();
			std::wstring key = CreateAniamtionKey(path);
			std::wstring fullName = path + L"\\" + filename;
			Image* image = ResourceManager::GetInstance()->Load<Image>(key + cnt, fullName);
			images.push_back(image);

			// 제일큰 리소스의 크기 셋팅
			if (width < image->GetWidth())
				width = image->GetWidth();

			if (height < image->GetHeight())
				height = image->GetHeight();

			fileCount++;
		}

		mSpriteSheet = Image::Create(name, width * fileCount, height);
		int index = 0;
		for (Image* image : images)
		{
			BitBlt(mSpriteSheet->GetDC(), width * index, 0, image->GetWidth(), image->GetHeight(), 
				image->GetDC(), 0, 0, SRCCOPY);

			index++;
		}

		Animator::CreateAnimation(name, mSpriteSheet
			, Vector2(0.0f, 0.0f), Vector2(width, height)
			, offset, fileCount, duration);
	}
	void Animator::Play(const std::wstring name, bool bLoop)
	{ 
		Animator::Events* events = FindEvents(name);
		if (events != nullptr)
			events->mStartEvent();

		Animation* prevAnimation = mPlayAnimation;
		mPlayAnimation = FindAnimation(name);
		mPlayAnimation->Reset();
		mbLoop = bLoop;

		FindImageEvent(mPlayAnimation->GetName());

		if (prevAnimation != mPlayAnimation)
		{
			if (events != nullptr)
				events->mEndEvent();
		}
	}

	bool Animator::bPlayAnimation()
	{
		if (mPlayAnimation)
			return true;
		
		return false;
	}

	Animator::Events* Animator::FindEvents(const std::wstring key)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(key);
		if (iter == mEvents.end())
		{
			return nullptr;
		}

		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring key)
	{
		Events* events = FindEvents(key);

		return events->mEndEvent.mEvent;
	}

	void Animator::PushImageEvent(const std::wstring key, UINT sheetIndex, std::function<void()> fun)
	{
		ImageEvent* event = new ImageEvent();
		event->mName = key;
		event->mSheetNum = sheetIndex;
		event->mEvent = fun;

		mImageEvent.push_back(event);
	}

	void Animator::ImageEventCheck()
	{
		if (mCurEvent == nullptr)
			return;
		if (mCurEvent->mName != mPlayAnimation->GetName())
			return;
		if (mCurEvent->mSheetNum != mPlayAnimation->GetSpriteIndex())
			return;

		mCurEvent->mEvent();
		mCurEvent = nullptr;
		mEvent_Run = false;
	}

	void Animator::FindImageEvent(const std::wstring name)
	{
		if (mPlayAnimation == nullptr)
			return;
		for (ImageEvent* event : mImageEvent)
		{
			if (event->mName == name)
			{
				mCurEvent = event;
				mEvent_Run = true;
			}
		}
	}
}