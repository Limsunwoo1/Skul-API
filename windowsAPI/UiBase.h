#pragma once
#include "Entity.h"

namespace sw
{
	class Image;
	class UiBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}

			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		UiBase(eUIType type);
		virtual ~UiBase();

		// UI �� �ε� �Ǿ����� �Ҹ��� �ʱ�ȭ �Լ�
		void Initialize();

		// UI �� Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		void Active();

		// UI �� ��Ȱ��ȭ�Ǹ� �Ҹ��� �Լ�
		void InActive();

		// UI�� ������Ʈ �ɶ����� ȣ��Ǵ� �Լ�
		void Tick();
		void Render(HDC hdc);

		// UI�� ������� ȣ��Ǵ� �Լ�
		void UIClear();

		void ImageLoad(const std::wstring& key, const std::wstring& path);
		void SetChild(Vector2 vector, UiBase* child);

		eUIType GetType() { return mType; }
		bool GetIsFullScreen() { return mbFullScreen; }
		void SetIsFullScreen(bool enable) { mbFullScreen = enable; }
		void SetParent(UiBase* parent) { mParent = parent; }
		void SetPos(Vector2 pos) { mScreenPos = pos; }
		Vector2 GetPos() { return mScreenPos; }
		void SetSize(Vector2 size) { mSize = size; }
		Vector2 GetSize() { return mSize; }

	protected:
		UiBase* mParent;
		Image* mImage;
		Vector2 mScreenPos;
		Vector2 mPos;
		Vector2 mSize;

	private:
		virtual void OnInit() {};
		virtual void OnActive() {};
		virtual void OnInActive() {};
		virtual void OnTick() {};
		virtual void OnRender(HDC hdc) {};
		virtual void OnClear() {};

	protected:
		std::vector<pair<Vector2, UiBase*>> mChilds;

		eUIType mType;
		bool mbFullScreen;
		bool mbEnable;
	};
}

