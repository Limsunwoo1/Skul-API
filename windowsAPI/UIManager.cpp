#include "UIManager.h"
#include "Application.h"
#include "Panel.h"
#include "HpBar.h"

namespace sw
{
	UIManager::UIManager()
	{

	}

	UIManager::~UIManager()
	{
		for (auto ui : mUIs)
		{
			if (ui.second == nullptr)
				continue;

			delete ui.second;
			ui.second = nullptr;
		}
		mUIs.clear();
	}

	void UIManager::Initialize()
	{
		// 여기에서 ui 메모리에 할당하면 된다.
		Panel* PlayerHpPanel = new Panel(eUIType::HP_PANEL);
		PlayerHpPanel->ImageLoad(L"HpPanel", L"..\\Resource\\Ui\\Player_Normal_Frame 복사.bmp");
		PlayerHpPanel->SetPos(Vector2(250.f, 750.f));
		PlayerHpPanel->SetSize(Vector2(500, 196.f));
		mUIs.insert(std::make_pair(eUIType::HP_PANEL, PlayerHpPanel));

		HpBar* newUI = new HpBar(eUIType::HP);
		newUI->ImageLoad(L"Hp", L"..\\Resource\\Ui\\Player_SubBar3 복사.bmp");
		newUI->SetPos(Vector2(500.f, 500.f));
		newUI->SetSize(Vector2(350.f, 30.f));
		mUIs.insert(std::make_pair(eUIType::HP, newUI));

		HUD* charterpanel = new HUD(eUIType::Character_Panel);
		charterpanel->ImageLoad(L"SubSkulFrame", L"..\\Resource\\Ui\\Player_Subskull_Frame 복사.bmp");
		charterpanel->SetPos(Vector2(500.f, 500.f));
		charterpanel->SetSize(Vector2(90.f, 90.f));
		mUIs.insert(std::make_pair(eUIType::Character_Panel, charterpanel));

		HUD* skilpanel = new HUD(eUIType::Skil_Panel);
		skilpanel->ImageLoad(L"SkilPanel", L"..\\Resource\\Ui\\Player_Subskill2_Frame 복사.bmp");
		skilpanel->SetPos(Vector2(500.f, 500.f));
		skilpanel->SetSize(Vector2(80.f, 80.f));
		mUIs.insert(std::make_pair(eUIType::Skil_Panel, skilpanel));

		PlayerHpPanel->SetChild(Vector2(-122.f, 32.f), newUI);
		PlayerHpPanel->SetChild(Vector2(-195.f, 40.f), charterpanel);
		PlayerHpPanel->SetChild(Vector2(40.f, -10.f), skilpanel);
		/*newUI = new UiBase(eUIType::MP);
		mUIs.insert(std::make_pair(eUIType::MP, newUI));

		newUI = new UiBase(eUIType::SHOP);
		mUIs.insert(std::make_pair(eUIType::SHOP, newUI));

		newUI = new UiBase(eUIType::INVENTORY);
		mUIs.insert(std::make_pair(eUIType::INVENTORY, newUI));

		newUI = new UiBase(eUIType::OPTION);
		mUIs.insert(std::make_pair(eUIType::OPTION, newUI));*/
		/*Push(eUIType::HP_PANEL);
		Push(eUIType::HP);
		Push(eUIType::Character_Panel);
		Push(eUIType::Skil_Panel);*/
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

		std::map<UINT, pair<UiBase*, UiBase*>>::iterator iter;
		iter = mMonsterHp.begin();
		for (; iter != mMonsterHp.end(); ++iter)
		{
			if (iter->second.first && iter->second.second)
			{
				iter->second.first->Tick();
				Vector2 pos = iter->second.first->GetPos();
				Vector2 size = iter->second.first->GetSize();

				iter->second.second->SetPos(Vector2(pos.x - (size.x * 0.5f), pos.y - (size.y * 0.5f)));
				iter->second.second->Tick();
			}
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
		std::stack<UiBase*> tempStack;

		// 뒤집어서랜더링을 해준다.
		while (!uiBases.empty())
		{
			UiBase* uiBase = uiBases.top();
			tempStack.push(uiBase);
			uiBases.pop();
		}

		while (!tempStack.empty())
		{
			UiBase* uiBase = tempStack.top();
			if (uiBase != nullptr)
			{
				uiBase->Render(hdc);
			}
			tempStack.pop();
		}

		std::map<UINT, pair<UiBase*, UiBase*>>::iterator iter;
		iter = mMonsterHp.begin();
		for (;iter != mMonsterHp.end(); ++iter)
		{
			if (iter->second.first && iter->second.second)
			{
				iter->second.first->Render(hdc);
				iter->second.second->Render(hdc);
			}
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
				uiBase->InActive();
				uiBase->UIClear();
			}
			else
			{
				tempStack.push(uiBase);
			}

		}

		// UI 재정렬
		while (tempStack.size())
		{
			uiBase = tempStack.top();
			tempStack.pop();
			mUiBases.push(uiBase);
		}
	}
	inline void UIManager::DeleteMonsterHp(UINT key)
	{
		std::map<UINT, pair<UiBase*, UiBase*>>::iterator iter;
		iter = mMonsterHp.find(key);
		if (iter == mMonsterHp.end())
			return;

		delete iter->second.first;
		delete iter->second.second;
		mMonsterHp.erase(iter);
	}
}
