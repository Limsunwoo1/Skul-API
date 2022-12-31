#pragma once
#include "GameObject.h"

namespace sw
{
	class Animator;
	typedef std::function<void(GameObject* object)> TColliderEvent;
	class ObjectProjecTile : public GameObject
	{
	public:
		ObjectProjecTile();
		~ObjectProjecTile();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void Initialize() override;

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void SetTarget(GameObject* object) { mTarget = object; }
		GameObject* GetTarget() { return mTarget; }

		void SetReuse_Time(float speed) {mReuse_Time = speed; }
		float GetReuse_Time() { return mReuse_Time; }

		void SetOffset(Vector2 offset) { mOffeset = offset; }
		Vector2 GetOffset() { return mOffeset; }

		void SetEvent(const TColliderEvent& event);

		void SetEffectName(const std::wstring& name) { mEffectName = name; }
		std::wstring GetEffectName() { return mEffectName; }

		void SetStartOffset(float offset = 0.0f) {mStartOffset = offset;}
		float GetStartOffset() { return mStartOffset; }

		void SetNotMove(bool move) { mNotMove = move; }
		bool GetNotMove() { return mNotMove; }

		Vector2 GetDirVec() { return mDirVec; }
		void SetDirVec(float x, float y) { mDirVec = Vector2(x, y); }
		void SetDirVec(Vector2 dir, int speed) { SetDirVec(dir.x, dir.y), SetSpeed(speed); }

		int GetSpeed() { return mSpeed; }
		void SetSpeed(int speed) { mSpeed = speed; }
	private:
		TColliderEvent Event;
		Animator* mAnimator;
		GameObject* mTarget;

		Vector2 mOffeset;
		Vector2 mDirVec;

		int mSpeed;

		float mDelta;
		float mReuse_Time;
		float mStartOffset;

		bool mAble;
		bool mNotMove;

		std::wstring mEffectName;
		std::unordered_map<UINT32, float> mColiedList;
	};
}

