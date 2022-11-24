#pragma once
#include "Common.h"

namespace sw
{	
	enum class EventType
	{
		NONE,
		AddObejct,
		DeleteObject,
		End,
	};

	struct EventInfo
	{
		EventType Type;
		void* Parameter1;
		void* Parameter2;
		void* Parameter3;


		EventInfo() : Type(EventType::NONE), Parameter1(nullptr), Parameter2(nullptr), Parameter3(nullptr) {};
		EventInfo(EventType InType) : Type(InType), Parameter1(nullptr), Parameter2(nullptr), Parameter3(nullptr) {};
		EventInfo(EventType InType, void* InParameter1) : Type(InType), Parameter1(InParameter1), Parameter2(nullptr), Parameter3(nullptr) {};
		EventInfo(EventType InType, void* InParameter1, void* InParameter2) : Type(InType), Parameter1(InParameter1), Parameter2(InParameter2), Parameter3(nullptr) {};
		EventInfo(EventType InType, void* InParameter1, void* InParameter2, void* InParameter3) : Type(InType), Parameter1(InParameter1), Parameter2(InParameter2), Parameter3(InParameter3) {};

		~EventInfo() = default;
	};

	class GameObject;
	class EventManager
	{
		SINGLE(EventManager);

	public:
		void Tick();
		void EventPush(EventInfo& InEvent) { mEventList.push(InEvent); }

	private:
		std::queue<EventInfo> mEventList;
	};
}

