#include "HUD.h"
#include "Image.h"

namespace sw
{
	HUD::HUD(eUIType type)
		: UiBase(type)
		, mbMouseOn(false)
	{

	}
	HUD::~HUD()
	{

	}

	void HUD::OnInit()
	{
	}

	void HUD::OnActive()
	{
	}

	void HUD::OnInActive()
	{
	}

	void HUD::OnTick()
	{
	}

	void HUD::OnRender(HDC hdc)
	{
		if (mImage == nullptr)
			return;
		
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() , mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

	}

	void HUD::OnClear()
	{
	}

}