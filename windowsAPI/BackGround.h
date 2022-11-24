#pragma once
#include "GameObject.h"

namespace sw
{
	class Image;
	class BackGround : public GameObject
	{
	public:
		BackGround();
		virtual ~BackGround();

		virtual void Tick() override;
		virtual void Initialize() override;
		virtual void Render(HDC hdc) override;

		void SetImage(const std::wstring& key, const std::wstring& filename);

	private:
		Image* mImage;
	};
}

