#pragma once
#include "GameObject.h"

namespace sw
{
	class KingObject : public GameObject
	{
	public:
		KingObject();
		~KingObject();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		void Init();

		void SetEndding(bool end) { mEndding = end; }
	private:
		float mDelta;
		bool mEndding;
	};
}

