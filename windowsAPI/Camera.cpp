#include "Camera.h"
#include "Application.h"
#include "Input.h"
#include "Time.h"
#include"GameObject.h"
#include "Image.h"
#include "Time.h"

namespace sw
{
	Camera::Camera()
		: mResolution(Vector2::Zero) // 화면 해상도
		, mLookPosition(Vector2::Zero)
		, mDistance(Vector2::Zero) // 해상도 중ㅇ심좌표와 현제 카메라의 간격차
		, mTarget(nullptr)
		, mEffect(eCameraEffect::None)
		, mCutton(nullptr)
		, mCuttonAlpha(0.0f)
		, mEndTime(5.0f)
	{

	}

	Camera::~Camera()
	{

	}

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();
		mResolution = Vector2(data.width, data.height);
		mLookPosition = (mResolution / 2.0f);

		mResolution = Vector2(1280, 800);

		mCutton = Image::Create(L"CameraCutton", 1600, 900);
		mEffect = eCameraEffect::None;
	}

	void Camera::Tick()
	{
		if (mAlphaTime <= mEndTime)
		{
			mAlphaTime += Time::GetInstance()->DeltaTime();
			float ratio = (mAlphaTime / mEndTime);

			if (eCameraEffect::FadeIn == mEffect)
			{
				mCuttonAlpha = 1.0f - ratio;
			}
			else if (eCameraEffect::FadeOut == mEffect)
			{
				mCuttonAlpha = ratio;
			}
		}

		if (KEY_PRESSE(eKeyCode::UP))
		{
			mLookPosition.y -= 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::DOWN))
		{
			mLookPosition.y += 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			mLookPosition.x -= 600.0f * Time::GetInstance()->DeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			mLookPosition.x += 600.0f * Time::GetInstance()->DeltaTime();
		}


		if (mTarget != nullptr)
			mLookPosition = mTarget->GetPos();

		if (mLookPosition.x < 0)
			mLookPosition.x = 0;
		if (mLookPosition.x > 1600)
			mLookPosition.x = 1600;

		if (mLookPosition.y < 0)
			mLookPosition.y = 0;
		if (mLookPosition.y > 900)
			mLookPosition.y = 900;

		mDistance = mLookPosition - (mResolution / 2.0f);
	}

	void Camera::Render(HDC hdc)
	{
		if (mEffect == eCameraEffect::None)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = 0;
		func.SourceConstantAlpha = (BYTE)(255.0f * mCuttonAlpha);

		float width = Application::GetInstance().GetWindowData().width;
		float height = Application::GetInstance().GetWindowData().height;
		AlphaBlend(hdc, 0, 0
			, width, height
			, mCutton->GetDC(), 0, 0
			, mCutton->GetWidth(), mCutton->GetHeight()
			, func);
	}
}