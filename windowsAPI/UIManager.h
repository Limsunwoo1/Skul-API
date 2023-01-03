#pragma once
#include "Common.h"
#include "UiBase.h"

namespace sw
{
	/// <summary>
	/// 플레이어의 조작에 영향을 받지 않죠 (위치 크기등등)
	/// 전체 화면 UI
	/// 기본 UI 
	/// HUD 이미지와 정보만 잇는 UI
	/// 버튼
	/// 내 UI 내 자식구조로 여러가지 다른 ui들을 구성해서
	/// 같이 움직이는 하나의 큰 UI 도 될수 있따.
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

