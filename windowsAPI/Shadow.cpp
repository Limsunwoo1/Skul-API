#include "Shadow.h"
#include "Image.h"
#include "PlayerBase.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Effect.h"
#include "Camera.h"

namespace sw
{
	Shadow::Shadow()
		: mDelta(0.0f)
		, mTarget(nullptr)
		, mShdowMax(10)
		, mCurEffect(0)
	{
	}
	Shadow::~Shadow()
	{
		for (Effect* effect : mShadows)
		{
			if (!effect)
				continue;

			delete effect;
			effect = nullptr;
		}
		mShadows.clear();
	}

	void Shadow::Initialize(std::wstring key, std::wstring path)
	{
		for (int i = 0 ; i < mShdowMax; i++)
		{
			Effect* effect = new Effect();
			effect->SetImage(key, path);
			mShadows.push_back(effect);
		}
	}

	void Shadow::Tick()
	{
		if (mTarget == nullptr)
			return;
		if (!mTarget->GetIsShadow())
			return;

		if (mCurEffect >= 10)
		{
			mTarget->SetIsShadow(false);
			mCurEffect = 0;
			return;
		}

		mDelta += Time::GetInstance()->DeltaTime();
		if (mDelta >= 0.03f)
		{
			mShadows[mCurEffect]->SetPos(mTarget->GetPos());
			mCurEffect++;
			mDelta -= 0.03f;
		}

		for (int i = 0; i < mCurEffect; ++i)
		{
			mShadows[i]->Tick();
		}
		LOG(STRING("½¦µµ¾î Æ½"))
	}


	void Shadow::Render(HDC hdc)
	{
		LOG(STRING("½¦µµ¾î ·£´õ"))
		if (mTarget == nullptr)
			return;
		if (!mTarget->GetIsShadow())
			return;

		for (int i = 0; i < mCurEffect; ++i)
		{
			mShadows[i]->Render(hdc);
		}

	}

	void Shadow::SetTarget(PlayerBase* target)
	{
		mTarget = target;
		for (Effect* effect : mShadows)
		{
			effect->SetTarget(target);
		}
	}
}