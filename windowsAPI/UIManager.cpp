#include "UIManager.h"
#include "Application.h"

namespace sw
{
	UIManager::UIManager()
	{

	}

	UIManager::~UIManager()
	{

	}

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.

		UiBase* newUI = new UiBase(eUIType::HP);
		mUIs.insert(std::make_pair(eUIType::HP, newUI));

		newUI = new UiBase(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, newUI));

		newUI = new UiBase(eUIType::SHOP);
		mUIs.insert(std::make_pair(eUIType::SHOP, newUI));

		newUI = new UiBase(eUIType::INVENTORY);
		mUIs.insert(std::make_pair(eUIType::INVENTORY, newUI));

		newUI = new UiBase(eUIType::OPTION);
		mUIs.insert(std::make_pair(eUIType::OPTION, newUI));

	}

	void UIManager::OnLoad(eUIType type)
	{
		std::unordered_map<eUIType, UiBase*>::iterator iter = mUIs.find(type);
		if (iter == mUIs.end())
		{
			OnFail();
			return;
		}

		OnComplete(iter->second);
	}

	void UIManager::Tick()
	{
		
		std::stack<UiBase*> uiBases = mUiBases;

		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Tick();
			}
			uiBases.pop();
		}

		if (mRequestUIQueue.size() > 0)
		{
			//UI 로드 해줘
			eUIType requestUI = mRequestUIQueue.front();
			mRequestUIQueue.pop();

			OnLoad(requestUI);
		}
	}


	void UIManager::Render(HDC hdc)
	{
		std::stack<UiBase*> uiBases = mUiBases;
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			uiBases.pop();
		}
	}
	void UIManager::OnComplete(UiBase* addUI)
	{
		if (addUI == nullptr)
			return;

		addUI->Initialize();
		addUI->Active();
		addUI->Tick();

		// addUI 가 전체화면 이면
		// Stack 안에 최상위 전체화면 Ui 를 꺼준다
		if (addUI->GetIsFullScreen())
		{
			std::stack<UiBase*>uiBases = mUiBases;
			while (!uiBases.empty())
			{
				UiBase* uiBase = uiBases.top();
				uiBases.pop();

				if (uiBase->GetIsFullScreen())
				{
					uiBase->InActive();
				}
			}
		}

		mUiBases.push(addUI);
	}
	void UIManager::OnFail()
	{
		mCurrentData = nullptr;
	}
	void UIManager::Push(eUIType type)
	{
		mRequestUIQueue.push(type);
	}

	void UIManager::Pop(eUIType type)
	{
		if (mUiBases.size() <= 0)
			return;

		std::stack<UiBase*> tempStack;

		UiBase* uiBase = nullptr;
		while (mUiBases.size() > 0)
		{
			uiBase = mUiBases.top();
			mUiBases.pop();
			// pop하는 ui가 전체화면 일경우에,
			// 남은 ui중에 전체화면인 가장 상단의 ui 를 활성화 해주어야한다.
			if (uiBase->GetType() == type)
			{
				if (uiBase->GetIsFullScreen())
				{
					std::stack<UiBase*> uiBases = mUiBases;

					while (!uiBases.empty())
					{
						UiBase* tempUI = uiBases.top();
						uiBases.pop();

						if (tempUI->GetIsFullScreen())
						{
							tempUI->Active();
							break;
						}
					}
				}
			}

		}
	}
}
