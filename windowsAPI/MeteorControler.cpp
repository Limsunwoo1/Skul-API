#include "MeteorControler.h"
#include <ctime>
#include "Time.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Meteor.h"
#include "Collider.h"
#include "Animator.h"

namespace sw
{
	MeteorControler MeteorControler::meteorControler;

	void MeteorControler::Tick()
	{
		/*for (GameObject* obj : Meteors)
		{
			if (!obj)
				continue;

			obj->Tick();
		}*/

		mDeltaTime += Time::GetInstance()->DeltaTime();
		if (mDeltaTime > 1.0f)
		{
			//Meteor* meteor = new Meteor();
			//float x = rand() % 1921;
			//meteor->SetPos({x, -1});

			//meteor->AddComponent(new Collider());
			//meteor->AddComponent(new Animator());

			//// Event»ý¼º
			//EventInfo info;
			//info.Type = EventType::AddObejct;
			//info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjectTile);
			//info.Parameter2 = meteor;
			//EventManager::GetInstance()->EventPush(info);

			//Meteors.push_back(meteor);

			mDeltaTime -= 0.5f;
		}
	}
	void MeteorControler::Render(HDC hdc)
	{
		int cnt = 0;
		for (GameObject* obj : Meteors)
		{
			if (cnt == 0)
			{
				EventInfo info;
				info.Type = EventType::DeleteObject;
				info.Parameter1 = new eColliderLayer(eColliderLayer::Monster_ProjectTile);
				info.Parameter2 = obj;
				EventManager::GetInstance()->EventPush(info);
				cnt++;
			}

			int r = rand() % 255;
			int g = rand() % 255;
			int b = rand() % 255;

			HBRUSH brush = CreateSolidBrush(RGB(r, g, b));
			Brush Curbrush(hdc, brush);

			HPEN pen = CreatePen(PS_SOLID, 2, RGB(b, g, r));
			Pen CurPen(hdc, pen);

			//obj->Render(hdc);
		}
	}

	MeteorControler::MeteorControler()
	{
		srand((unsigned int)time(NULL));
	}
	MeteorControler::~MeteorControler()
	{
		
	}
}