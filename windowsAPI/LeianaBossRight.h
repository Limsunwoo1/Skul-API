#pragma once
#include "BossMonster.h"


namespace sw
{
	class Scene;
	class LeianaControler;
	class ObjectProjecTile;
	class LeianaBossRight : public BossMonster
	{
	public:
		LeianaBossRight();
		~LeianaBossRight();

		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void Initialize() override;
		virtual void InitializeAnimation() override;
		virtual void InitalizeCollider() override;
		virtual void InitalizeProjecTile() override;

		virtual void Idle() override;
		virtual void Patton1() override;
		virtual void Patton2() override;
		virtual void Patton3() override;
		virtual void Patton4() override;

		virtual void Patton1_Stand_by( bool type = true) override;
		virtual void Patton1_Progress() override;
		virtual void Patton2_Stand_by( bool type = true) override;
		virtual void Patton2_Progress() override;
		virtual void Patton3_Stand_by( bool type = true) override;
		virtual void Patton3_Progress() override;
		virtual void Patton4_Stand_by( bool type = true) override;
		virtual void Patton4_Progress() override;

		void ScreenOut();
		void ScreenIn();

		void SetOwer(LeianaControler* owner) { mOwner = owner; }
		LeianaControler* GetOwner() { return mOwner; }

		float GetScreenLSpawnX() { return mLScreenSpawnX; }
		void SetScreenLSpawnX(float x) { mLScreenSpawnX = x; }

		float GetScreenRSpawnX() { return mRScreenSpawnX; }
		void SetScreenRSpawnX(float x) { mRScreenSpawnX = x; }

		float GetScreenSpawnY() { return mScreenSpawnY; }
		void SetScreenSpawnY(float y) { mScreenSpawnY = y; }

		float GetScreenLOutX() { return mLScreenOutX; }
		void SetScreenScreenLOutX(float x) { mLScreenOutX = x; }

		float GetScreenROutX() { return mRScreenOutX; }
		void SetScreenROutX(float x) { mRScreenOutX = x; }

		float GetScreenOutY() { return mScreenOutY; }
		void SetScreenOutY(float y) { mScreenOutY = y; }

		bool GetScreenIn() { return mbIn; }
		void SetScreenIn(bool in) { mbIn = in; }

		bool GetScreenOut() { return mbOut; }
		void SetScreenOut(bool out) { mbOut = out; }

		bool GetHold() { return mHold; }
		void SetHold(bool hold) { mHold = hold; }

		void OffProjecTile();
	private:
		LeianaControler* mOwner;
		ObjectProjecTile* mProjecTile;
		bool mbIn;
		bool mbOut;
		bool mHold;

		float mLScreenSpawnX;
		float mRScreenSpawnX;
		float mScreenSpawnY;

		float mLScreenOutX;
		float mRScreenOutX;
		float mScreenOutY;

		Vector2 mDirVec;
		UINT mSpeed;
	};
}

