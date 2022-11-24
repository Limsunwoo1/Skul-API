#pragma once
#include "GameObject.h"


namespace sw
{
	class Meteor;
	class MeteorControler
	{
	public:
		static MeteorControler* GetMeteorControler() {return &meteorControler;}
		 void Tick();
		 void Render(HDC hdc) ;

	private:
		MeteorControler();
		virtual ~MeteorControler();

	private:
		std::vector<Meteor*> Meteors;
		float mDeltaTime = 0.0f;

		static MeteorControler meteorControler;
	};
}

