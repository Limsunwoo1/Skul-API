#include "Effect.h"
#include "PlayerBase.h"
#include "Image.h"
#include "ResourceManager.h"
#include "Camera.h"

namespace sw
{
	Effect::Effect()
		: mImage(nullptr)
		, mTarget(nullptr)
	{

	}

	Effect::~Effect()
	{

	}

	void Effect::SetImage(std::wstring key, std::wstring path)
	{
		mImage = ResourceManager::GetInstance()->Load<Image>(key, path);
	}

	void Effect::SetTarget(PlayerBase* target)
	{
		mTarget = target;
	}

	void Effect::Tick()
	{
	}

	void Effect::Render(HDC hdc)
	{
		if (mTarget == nullptr)
			return;
		if (mImage == nullptr)
			return;

		Vector2 pos = Camera::GetInstance()->CalculatePos(mPos);
		pos -= mOffset;
		Vector2 scale = GetScale();

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 100; // 0 - 225

		AlphaBlend(hdc
			, (int)pos.x - ((mImage->GetWidth()* 0.5f) * (scale.x * 0.5f))
			, (int)pos.y - ((mImage->GetHeight()* 0.5f) * (scale.x * 0.5f))
			, (int)mImage->GetWidth() * (scale.y * 0.5f)
			, (int)mImage->GetHeight() * (scale.y * 0.5f)
			, mImage->GetDC()
			, (int)0
			, (int)0
			, (int)mImage->GetWidth()
			, (int)mImage->GetHeight()
			, func);
	}
}
