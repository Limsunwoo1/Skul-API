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

		inline void SetUiInstance(eUIType type, UiBase* ui) { mUIs.insert(make_pair(type, ui)); }
		inline void SetMonsterInstance(UINT key,UiBase* base1, UiBase* base2) { mMonsterHp.insert(make_pair(key,make_pair(base1, base2))); }
		inline void DeleteMonsterHp(UINT key);
		inline void MonsterHpClear() { mMonsterHp.clear(); }
	private:
		std::unordered_map<eUIType, UiBase*> mUIs;
		std::queue<eUIType> mRequestUIQueue;
		std::stack<UiBase*> mUiBases;
		std::map<UINT,pair<UiBase*, UiBase*>> mMonsterHp;
		UiBase* mCurrentData;
	};
}

