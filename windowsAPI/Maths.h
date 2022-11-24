#pragma once
#include <math.h>

namespace sw
{
	struct Vector2
	{
		static Vector2 Zero;
		static Vector2 One;
		static Vector2 Right;
		static Vector2 Left;
		static Vector2 Up;
		static Vector2 Down;

		float x;
		float y;

		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void clear()
		{
			x = 0.0f;
			y = 0.0f;
		}

		Vector2 operator/(const float& value) const
		{
			Vector2 temp;
			temp.x = x / value;
			temp.y = y / value;

			return temp;
		}

		Vector2 operator -()
		{
			return Vector2(-x, -y);
		}

		Vector2 operator+(const Vector2& other) const
		{
			Vector2 temp;
			temp.x = this->x + other.x;
			temp.y = this->y + other.y;

			return temp;
		}

		Vector2 operator-(const Vector2& other) const
		{
			Vector2 temp;
			temp.x = this->x - other.x;
			temp.y = this->y - other.y;

			return temp;
		}


		Vector2 operator* (const float& value) const
		{
			Vector2 temp;
			temp.x = this->x * value;
			temp.y = this->y * value;

			return temp;
		}

		Vector2 operator/(const float& value)
		{
			Vector2 temp;

			temp.x = x / value;
			temp.y = y / value;

			return temp;
		}

		Vector2& operator *=(const float value)
		{
			x *= value;
			y *= value;

			return *this;
		}

		Vector2 operator += (const Vector2& other)
		{
			this->x += other.x;
			this->y += other.y;
			return *this;
		}

		Vector2 operator -= (const Vector2& other)
		{
			this->x -= other.x;
			this->y -= other.y;
			return *this;
		}

		bool operator ==(const Vector2& other)
		{
			return (x == other.x && y == other.y);
		}

		float Length()
		{
			return sqrtf(x * x + y * y);
		}

		Vector2& Normalize()
		{
			// 벡터의 길이를 구하고 각 원소를 길이로 나누어 준다
			// 벡터의 정규화, 단위 벡터
			float length = Length();
			x /= length;
			y /= length;

			return *this;
		}

		Vector2(const Vector2& other) = default;
		Vector2() = default;
		~Vector2() = default;
	};
	typedef Vector2 Vector2D;
	typedef Vector2 Pos;
}