#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class Tile : public GameObject
	{
	public:

		Tile(Vector2 pos);
		virtual ~Tile();

		void Initialize(Image* atlas, int index);
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void SetIndex(UINT index);
		UINT GetIndex() { return mIndex; }

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		void CheckCollider(Collider* other);
		void Top_Bottom_Collider(Collider* other);
		void SetAngle();
	private:
		Image* mAtlas;

		UINT mIndex;
		UINT mX;
		UINT mY;

		float mAngle;
	};
}

