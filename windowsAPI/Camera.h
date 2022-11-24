#pragma once
#include "Common.h"

namespace sw
{
	class Image;
	class GameObject;
	class Camera
	{
		SINGLE(Camera);

	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);
		Vector2 CalculatePos(Vector2 pos) { return pos - mDistance; }
		void SetTarget(GameObject* Gameobj) {mTarget = Gameobj;}

		void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

	private:
		Vector2 mResolution; // 화면 해상도
		Vector2 mLookPosition;
		Vector2 mDistance; // 해상도 중ㅇ심좌표와 현제 카메라의 간격차
		GameObject* mTarget;

		eCameraEffect mEffect;
		Image* mCutton;		// 검정색이미지
		float mAlphaTime;
		float mCuttonAlpha;
		float mEndTime;
	};
}

