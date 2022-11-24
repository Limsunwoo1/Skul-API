#pragma once
#include "Common.h"
#include "UiBase.h"

namespace sw
{
	/// <summary>
	/// �÷��̾��� ���ۿ� ������ ���� ���� (��ġ ũ����)
	/// ��ü ȭ�� UI
	/// �⺻ UI 
	/// HUD �̹����� ������ �մ� UI
	/// ��ư
	/// �� UI �� �ڽı����� �������� �ٸ� ui���� �����ؼ�
	/// ���� �����̴� �ϳ��� ū UI �� �ɼ� �ֵ�.
	/// </summary>
	
	class UIManager
	{
		SINGLE(UIManager);

	public:
		void Initialize();
		void Tick();
		void Render(HDC hdc);
		void OnComplete(UiBase* addUI);
		void OnFail();
		void OnLoad(eUIType type);

		void Push(eUIType type);
		void Pop(eUIType type);

		template<typename T>
		inline T* GetUiInstance(eUIType type)
		{
			return dynamic_cast<T*>(mUIs[type]);
		}

	private:
		std::unordered_map<eUIType, UiBase*> mUIs;
		std::queue<eUIType> mRequestUIQueue;
		std::stack<UiBase*> mUiBases;
		UiBase* mCurrentData;
	};
}

