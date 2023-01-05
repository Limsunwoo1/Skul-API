#include "HpBar.h"
#include "Image.h"
#include "GameObject.h"
#include "MonsterBase.h"
namespace sw
{
	HpBar::HpBar(eUIType type)
		: HUD(type)
		, mMonsterHP(false)
	{

	}

	HpBar::~HpBar()
	{

	}

	void HpBar::OnTick()
	{
		if (mTarget && mMonsterHP)
		{
			Vector2 size = GetSize();
			size.x = mTarget->GetHp() * 5.f;
			SetSize(size);
			return;
		}
		
		if (mTarget && !mMonsterHP)
		{
			float x = mTarget->GetHp() / mTargetMaxHp;
			float a = mMaxSizeX * x;
			SetSize(Vector2(mMaxSizeX * x, GetSize().y));
			return;
		}
	}

	void HpBar::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, mScreenPos.x, mScreenPos.y
			, mSize.x, mSize.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
}