#include "Shadow.h"
#include "Image.h"
#include "Player.h"
#include "ResourceManager.h"
#include "Time.h"
#include "Effect.h"

namespace sw
{
	Shadow::Shadow()
		: mDuraction(0.0f)
		, mTarget(nullptr)
		, mShdowMax(10)
		, mCurEffect(0)
	{
	}
	Shadow::~Shadow()
	{

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


	void Shadow::Render(HDC hdc)
	{
		if (mTarget == nullptr)
			return;
		if (!mTarget->GetIsShadow())
			return;

		// target pos 를받아 일정간격으로 세팅
		mDuraction += Time::GetInstance()->DeltaTime();
		if (mDuraction >= 0.2f)
		{
			mShadows[mCurEffect]->SetPos(mTarget->GetPos());
			mCurEffect++;
			mDuraction -= 0.2f;
		}

		for (int i = 0; i < mCurEffect; ++i)
		{
			mShadows[i]->Render(hdc);
		}

		if (mCurEffect >= 10)
			mCurEffect = 0;
	}

	void Shadow::SetTarget(Player* target)
	{
		mTarget = target;
		for (Effect* effect : mShadows)
		{
			effect->SetTarget(target);
		}
	}
}