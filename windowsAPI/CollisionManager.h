#pragma once
#include "Common.h"

namespace sw
{
	class Collider;
	class Scene;
	class CollisionManager
	{
		SINGLE(CollisionManager);

	public:
		void Tick();
		std::vector<Collider*> GetColliders(eColliderLayer type, Box box);
		void SetLayer(eColliderLayer left, eColliderLayer right, bool value = true);

	private:
		void LayerCollision(Scene* scene, eColliderLayer left, eColliderLayer right);
		void ColliderCollision(Collider* left, Collider* right);
		bool Intersect(Collider* left, Collider* rgiht);
		bool Intersect(Box box, Collider* rgiht);

	private:
		WORD mMatrix[COLLIDER_LAYER];
		std::map<UINT64, bool> mCollisionInformation;

		std::unordered_map<eColliderLayer,Box> mEventColllsion;
	};
}

