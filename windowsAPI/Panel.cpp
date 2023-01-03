#include "Panel.h"
#include "Image.h"
#include "GameObject.h"
#include "Camera.h"
#include "HpBar.h"
#include "Collider.h"
#include "MonsterBase.h"

namespace sw
{
	Panel::Panel(eUIType type)
		: UiBase(type)
	{

	}
	Panel::~Panel()
	{

	}

	void Panel::OnInit()
	{
	}

	void Panel::OnActive()
	{
	}

	void Panel::OnInActive()
	{
	}

	void Panel::OnTick()
	{
		if (mTarget)
		{
			MonsterBase* monster = dynamic_cast<MonsterBase*>(mTarget);
			if (!monster)
				return;

			Vector2 pos = mTarget->GetPos();
			pos = Camera::GetInstance()->CalculatePos(pos);
			Vector2 colScale = mTarget->GetComponent<Collider>()->GetScale();
			SetPos(Vector2(pos.x, pos.y - ((colScale.y * 0.5f) + 30.f)));
		}

		for (int i = 0; i < mChilds.size(); ++i)
		{
			if (mChilds[i].second == nullptr)
				continue;

			UiBase* ui = mChilds[i].second;
			ui->SetPos(GetPos() + mChilds[i].first);
		}
	}

	void Panel::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, mScreenPos.x - (mSize.x * 0.5f), mScreenPos.y - (mSize.y * 0.5f)
			, mSize.x, mSize.y
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void Panel::OnClear()
	{
	}

	void Panel::SetChild(Vector2 vector, UiBase* child)
	{
		child->SetParent(this); 
		mChilds.push_back(make_pair(vector,child));
	}

}