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
		for (int i = 0; i < mChilds.size(); ++i)
		{
			if (mChilds[i].second == nullptr)
				continue;

			UiBase* ui = mChilds[i].second;
			ui->SetPos(GetPos() + mChilds[i].first);
		}
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

		AlphaBlend(hdc, mScreenPos.x - (mSize.x * 0.5f), mScreenPos.y - (mSize.y * 0.5f)
			,mSize.x ,mSize.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);

	}

	void HUD::OnClear()
	{
	}

}