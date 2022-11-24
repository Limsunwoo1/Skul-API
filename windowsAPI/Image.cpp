#include "Image.h"
#include "Application.h"
#include "ResourceManager.h"

namespace sw
{
	Image::Image()
		: mBitmap(NULL)
		, mHdc(NULL)
		, mWidth(0)
		, mHeight(0)
	{

	}

	Image::~Image()
	{
		HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
		ReleaseDC(hWnd, mHdc);
	}

	HRESULT Image::Load(const std::wstring& path)
	{
		mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), 
			IMAGE_BITMAP, 0, 0, 
			LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		if (!mBitmap)
		{
			return E_FAIL;
		}

		BITMAP bitInfo = {};
		GetObject(mBitmap, sizeof(BITMAP), &bitInfo);

		mWidth = bitInfo.bmWidth;
		mHeight = bitInfo.bmHeight;

		HDC mainDC = Application::GetInstance().GetWindowData().hdc;
		mHdc = CreateCompatibleDC(mainDC);

		HBITMAP prevBit = (HBITMAP)SelectObject(mHdc, mBitmap);
		DeleteObject(prevBit);

		return S_OK;
	}

	Pixel Image::GetPixelImage(int x, int y)
	{
		COLORREF rgba = GetPixel(mHdc, x, y);

		return Pixel(rgba);
	}

	void Image::SetPixel(int x, int y, Pixel pixel)
	{
		// 비트맵 좌표는 촤측하단이 0,0 
		// 윈도우좌표처럼 사용하려면 y를 반대로 바꾸어 주어야 한다.
		y = mHeight - (y + 1);

		Pixel* bitmapPixel = (Pixel*)mBitmap;
		bitmapPixel += (mWidth * y + x);

		*bitmapPixel = pixel;
	}

	Image* Image::Create(const std::wstring& key, UINT width, UINT height)
	{
		// 우선 기존 이미지가 있는지 체크
		Image* image = ResourceManager::GetInstance()->Find<Image>(key);
		if (image != nullptr)
		{
			MessageBox(nullptr, L"중복 키 이미지 생성", L"이미지 생성 실패!", MB_OK);
			return nullptr;
		}

		// 이미지를 생성해 줘야한다
		image = new Image();
		HDC mainhdc = Application::GetInstance().GetWindowDC();

		image->mBitmap = CreateCompatibleBitmap(mainhdc, width, height);
		image->mHdc = CreateCompatibleDC(mainhdc);

		if (image->mBitmap == NULL
			|| image->mHdc == NULL)
			return nullptr;

		// 새로 생성한 비트맵과 DC 를 서로 연결해 주어야함
		HBITMAP defaultBitmap = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
		DeleteObject(defaultBitmap);

		// 비드맵 정보 확인
		BITMAP bitmap = {};
		GetObject(image->mBitmap, sizeof(BITMAP), &bitmap);

		image->mWidth = bitmap.bmWidth;
		image->mHeight = bitmap.bmHeight;

		image->SetKey(key);
		ResourceManager::GetInstance()->Insert<Image>(key, image);

		return image;
	}
}
