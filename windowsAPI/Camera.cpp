#include "Camera.h"
#include "Application.h"
#include "Input.h"
#include "Time.h"
#include"GameObject.h"
#include "Image.h"
#include "SceneManager.h"

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
		, bToolMode(false)
		, bFreezCamera(false)
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

		mResolution = Vector2(1600, 900);

		mCutton = Image::Create(L"CameraCutton", 1600, 900);
		mEffect = eCameraEffect::None;

		if(SceneManager::GetInstance()->CheckCurScen(eSceneType::Tool))
			bToolMode = true;
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

		if (bToolMode)
		{
			if (KEY_PRESSE(eKeyCode::UP))
			{
				mLookPosition.y -= 1000 * Time::GetInstance()->DeltaTime();
			}
			if (KEY_PRESSE(eKeyCode::DOWN))
			{
				mLookPosition.y += 1000 * Time::GetInstance()->DeltaTime();
			}
			if (KEY_PRESSE(eKeyCode::LEFT))
			{
				mLookPosition.x -= 1000 * Time::GetInstance()->DeltaTime();
			}
			if (KEY_PRESSE(eKeyCode::RIGHT))
			{
				mLookPosition.x += 1000 * Time::GetInstance()->DeltaTime();
			}
		}
		else if (!bToolMode)
		{
			if (mTarget != nullptr)
				mLookPosition = mTarget->GetPos();

			if (mLookPosition.x + (mResolution.x * 0.5f) >= mCameraMaxPos.x)
				mLookPosition.x = mCameraMaxPos.x - (mResolution.x * 0.5f);
			else if(mLookPosition.x - (mResolution.x * 0.5f) <= mCameraLowPos.x)
				mLookPosition.x = mCameraLowPos.x + (mResolution.x * 0.5f);

			if (mLookPosition.y + (mResolution.y * 0.5f) >= mCameraMaxPos.y)
				mLookPosition.y = mCameraMaxPos.y - (mResolution.y * 0.5f);
			else if (mLookPosition.y - (mResolution.y * 0.5f) <= mCameraLowPos.y)
				mLookPosition.y = mCameraLowPos.y + (mResolution.y * 0.5f);
		}

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