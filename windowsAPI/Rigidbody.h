#pragma once
#include "Component.h"

namespace sw
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mbGround = isGround; }
		bool GetGround() { return mbGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

		bool GetFreez() { return bFreez; }
		void SetFreez(bool freez) { bFreez = freez; }
	private:
		// ���� �������� �̿��� �̵�
		float mMass;
		float mFriction;

		Vector2 mForce;		// ��
		Vector2 mVelocity; // �ӵ�
		Vector2 mAccelation; // ���ӵ�

		// �߷��� �̿��� ����
		Vector2 mGravity;
		bool mbGround;
		// ���� �ƽ���
		Vector2 mLimitVelocity;

		bool bFreez;
	};
}

