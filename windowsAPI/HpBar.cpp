#include "HpBar.h"
#include "Image.h"
#include "GameObject.h"
namespace sw
{
	HpBar::HpBar(eUIType type)
		: HUD(type)
	{

	}

	HpBar::~HpBar()
	{

	}

	void HpBar::OnTick()
	{
		if (mTarget)
		{
			Vector2 size = GetSize();
			size.x = mTarget->GetHp() * 5.f;
			SetSize(size);
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