#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"

namespace sw
{
	EventManager::EventManager()
	{

	}

	EventManager::~EventManager()
	{

	}

	void EventManager::Tick()
	{
		while (!mEventList.empty())
		{
			EventInfo& NewEvent = mEventList.front();

			switch (NewEvent.Type)
			{
				case EventType::AddObejct:
					{
						if (NewEvent.Parameter2)
						{
							SceneManager::GetInstance()->GetPlayScene()->
								AddGameObject(
									(GameObject*)NewEvent.Parameter2,
									*((eColliderLayer*)NewEvent.Parameter1));
						}
					}
					break;

				case EventType::DeleteObject:
					{
					SceneManager::GetInstance()->GetPlayScene()->
						DeleteGameObject(
							(GameObject*)NewEvent.Parameter2,
							*((eColliderLayer*)NewEvent.Parameter1));
					}
					break;
			}

			delete NewEvent.Parameter1;
			mEventList.pop();
		}
	}
}