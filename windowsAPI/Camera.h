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
		Vector2 GetDistance() { return mDistance; }
		void SetDistance(Vector2 lookpos) { mDistance = lookpos - (mResolution / 2.0f); }
		Vector2 GetLookPosition() { return mLookPosition; }
		void SetLookPosition(Vector2 pos) { mLookPosition = pos; }
		void SetTarget(GameObject* Gameobj) {mTarget = Gameobj;}
		void SetToolMode(bool able) { bToolMode = able; }

		void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

		bool GetFreezCamera() { return bFreezCamera; }
		void SetFreezCamera(bool ing) { bFreezCamera = ing; }

		Vector2 GetCameraMaxPos() { return mCameraMaxPos; }
		void SetCameraMaxPos(Vector2 pos) { mCameraMaxPos = pos; }

		Vector2 GetCameraLowPos() { return mCameraLowPos; }
		void SetCameraLowPos(Vector2 pos) { mCameraLowPos = pos; }
	private:
		Vector2 mResolution; // ȭ�� �ػ�
		Vector2 mLookPosition;
		Vector2 mDistance; // �ػ� �ߤ�����ǥ�� ���� ī�޶��� ������
		GameObject* mTarget;

		eCameraEffect mEffect;
		Image* mCutton;		// �������̹���
		float mAlphaTime;
		float mCuttonAlpha;
		float mEndTime;

		bool bFreezCamera;
		bool bToolMode;

		Vector2 mCameraMaxPos;
		Vector2 mCameraLowPos;
	};
}

