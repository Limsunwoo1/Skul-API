#include "BackGround.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Image.h"

namespace sw
{
	BackGround::BackGround()
		: mImage(nullptr)
		, mCamera(true)
		, Alph(true)
	{
		
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

		if(mCamera)
			pos = Camera::GetInstance()->CalculatePos(pos);
		pos += Camera::GetInstance()->GetDistance() * 0.2f;

		if (!Alph)
		{
			TransparentBlt(hdc,
				pos.x - (scale.x * 0.5f), pos.y - (scale.y * 0.5f),
				scale.x, scale.y,
				mImage->GetDC(),
				0, 0, mImage->GetWidth(), mImage->GetHeight(),
				RGB(255, 0, 255));
		}
		else
		{
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
		}
		
		GameObject::Render(hdc);
	}
	void BackGround::SetImage(const std::wstring& key, const std::wstring& filename)
	{
		std::wstring path = L"..\\Resource\\Image\\";
		path += filename;

		mImage = ResourceManager::GetInstance()->Load<Image>(key, path);
	}
}
