#include "Animation.h"
#include "GameObject.h"
#include "Image.h"
#include "Animator.h"
#include "Camera.h"
#include "Time.h"

namespace sw
{
	Animation::Animation()
	{

	}

	Animation::~Animation()
	{

	}

	void Animation::Tick()
	{
		if (mbComplete)
			return;

		mTime += Time::GetInstance()->DeltaTime();
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mSpriteSheet.size() <= mSpriteIndex + 1)
				mbComplete = true;
			else
				mSpriteIndex++;
		}
	}

	void Animation::Render(HDC hdc)
	{
		GameObject* gameobj = mAnimator->GetOwner();
		Vector2 pos = gameobj->GetPos();
		Vector2 scale = gameobj->GetScale();

		if (mAffectedCamera)
			pos = Camera::GetInstance()->CalculatePos(pos);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255; // 0 - 225

		pos += mSpriteSheet[mSpriteIndex].offest;

		/*TransparentBlt(hdc
			, (int)pos.x - scale.x / 2.0f
			, (int)pos.y - scale.y / 2.0f
			, (int)scale.x
			, (int)scale.y
			, mImage->GetDC()
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.x
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.y
			, (int)mSpriteSheet[mSpriteIndex].size.x
			, (int)mSpriteSheet[mSpriteIndex].size.y
			, RGB(255, 0, 255));*/

		AlphaBlend(hdc
			, (int)pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.0f
			, (int)pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.0f
			, (int)mSpriteSheet[mSpriteIndex].size.x
			, (int)mSpriteSheet[mSpriteIndex].size.y
			, mImage->GetDC()
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.x
			, (int)mSpriteSheet[mSpriteIndex].LeftTop.y
			, (int)mSpriteSheet[mSpriteIndex].size.x
			, (int)mSpriteSheet[mSpriteIndex].size.y
			, func);
	}

	void Animation::Create(Image* image, Vector2 leftTop, Vector2 size, Vector2 offest
		, UINT spriteLegnth, float duration, bool bAffectedCamera)
	{
		mImage = image;
		mAffectedCamera = bAffectedCamera;

		for (int i = 0; i < spriteLegnth; i++)
		{
			Sprite sprite;
			sprite.LeftTop.x = leftTop.x + (size.x * (float)i);
			sprite.LeftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offest = offest;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}

	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.0f;
		mbComplete = false;
	}


	// 한가지 이벤트만 추가하고 싶을시
	// SetEvent(nullptr, nullptr, fun3) == EndEvent추가
	
}