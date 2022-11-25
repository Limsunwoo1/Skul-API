#include "BackGround.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Image.h"

namespace sw
{
	BackGround::BackGround()
		: mImage(nullptr)
	{
		SetPos(Vector2(1920.f * 0.5f, 1080.f * 0.5f));
		SetScale(Vector2(1920.f, 1080.f));
	}

	BackGround::~BackGround()
	{

	}

	void BackGround::Initialize()
	{

	}

	void BackGround::Tick()
	{
		GameObject::Tick();
	}

	void BackGround::Render(HDC hdc)
	{
		if (mImage == nullptr)
			return;

		Vector2 pos = GetPos();
		Vector2 scale = GetScale();


		/*TransparentBlt(hdc,
			finalPos.x, finalPos.y,
			1920, 1080,
			mImage->GetDC(),
			0, 0, mImage->GetWidth(), mImage->GetHeight(),
			RGB(255, 0, 255));*/

		pos = Camera::GetInstance()->CalculatePos(pos);

		BLENDFUNCTION bf;
		bf.AlphaFormat = 0;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 255;

		AlphaBlend(hdc,
			pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f),
			scale.x, scale.y,
			mImage->GetDC(),
			0, 0,
			mImage->GetWidth(), mImage->GetHeight()
			, bf);
		
		GameObject::Render(hdc);
	}
	void BackGround::SetImage(const std::wstring& key, const std::wstring& filename)
	{
		std::wstring path = L"..\\Resource\\Image\\";
		path += filename;

		mImage = ResourceManager::GetInstance()->Load<Image>(key, path);
	}
}
