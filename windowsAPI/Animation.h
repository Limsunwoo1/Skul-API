#pragma once
#include "Entity.h"

namespace sw
{
	class Image;
	class Animator;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 LeftTop; // ���� ��� ������ǥ
			Vector2 size; // ����������κ��� �߶� ���α���
			Vector2 offest;
			float duration; // �ش� ������ ���� �ð�


			Sprite()
				: LeftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offest(Vector2::Zero)
				, duration(0.0f)
			{

			}
		};
		
	public:
		Animation();
		~Animation();

		void Tick();
		void Render(HDC hdc);
		void Create(Image* image
			, Vector2 leftTop, Vector2 size, Vector2 offest
			, UINT spriteLegnth, float duration
			, bool bAffectedCamera = true);

		void Reset();
		bool isComplete() { return mbComplete; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

		int GetAlpha() { return mAlpha; }
		void SetAlpha(int alpha) { mAlpha = alpha; }

		UINT GetSpriteIndex() { return mSpriteIndex; }

	private:
		Animator* mAnimator;
		Image* mImage;
		std::vector<Sprite> mSpriteSheet;
		UINT mSpriteIndex;
		int mAlpha;
		float mTime;

		bool mStart;
		bool mbComplete;
		bool End;
		bool mAffectedCamera;
	};
}

