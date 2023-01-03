#include "UiBase.h"
#include "ResourceManager.h"
#include "Image.h"

namespace sw
{
	UiBase::UiBase(eUIType type)
		: mType(type)
		, mbFullScreen(false)
		, mbEnable(false)
	{
		
	}

	UiBase::~UiBase()
	{

	}

	void UiBase::Initialize()
	{
		OnInit();
	}

	void UiBase::Active()
	{
		mbEnable = true;
		OnActive();
	}

	void UiBase::InActive()
	{
		mbEnable = false;
		OnInActive();
	}

	void UiBase::Tick()
	{
		if (mbEnable == false)
			return;

		OnTick();
	}

	void UiBase::Render(HDC hdc)
	{
		if (mbEnable == false)
			return;

		OnRender(hdc);
	}

	void UiBase::UIClear()
	{
		OnClear();
	}

	void UiBase::ImageLoad(const std::wstring& key, const std::wstring& path)
	{
		mImage = ResourceManager::GetInstance()->Load<Image>(key, path);

		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
	}

	void UiBase::SetChild(Vector2 vector, UiBase* child)
	{
		child->SetParent(this);
		mChilds.push_back(make_pair(vector, child));
	}
}