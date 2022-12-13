#pragma once
#include <math.h>

#define PI 3.141592f

namespace sw
{
	class Vector2
	{
	public:
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

		void Clear()
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

		Vector2 operator+(const float& value) const
		{
			Vector2 temp;
			temp.x = this->x + value;
			temp.y = this->y + value;

			return temp;
		}

		Vector2 operator-(const Vector2& other) const
		{
			Vector2 temp;
			temp.x = this->x - other.x;
			temp.y = this->y - other.y;

			return temp;
		}

		Vector2 operator-(const float& value) const
		{
			Vector2 temp;
			temp.x = this->x - value;
			temp.y = this->y - value;

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

		bool operator !=(const Vector2& other)
		{
			return (x != other.x || y != other.y);
		}

		float Length()
		{
			float len = sqrtf((x * x) + (y * y));
			return len;
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


	namespace UtilMath
	{
		inline float ToRadian(float Degree)
		{
			return Degree * (PI / 180.f);
		}

		inline float ToDegree(float Radian)
		{
			return Radian * (180.f / PI);
		}

		inline float Sin(float Degree)
		{
			return sinf(ToRadian(Degree));
		}

		inline float Cos(float Degree)
		{
			return cosf(ToRadian(Degree));
		}

		// 회전
		inline sw::Vector2 Rotate(const sw::Vector2 value, float degree)
		{
			sw::Vector2 ret = sw::Vector2::Zero;
			float radian = ToRadian(degree);
			ret.x = value.x * cosf(radian) - value.y * sinf(radian);
			ret.y = value.x * sinf(radian) + value.y * cosf(radian);

			return ret;
		}

		inline float Dot(sw::Vector2& v1, sw::Vector2& v2)
		{
			return (v1.x * v2.x) + (v1.y * v2.y);
		}

		inline float Cross(sw::Vector2& v1, sw::Vector2& v2)
		{
			return (v1.x * v2.x) - (v1.y * v2.y);
		}

		/*float Lerp(float p1, float p2, float t)
		{
			return (1 - t) * p1 + t * p2;
		}

		sw::Vector2 LerpVector(sw::Vector2 v1, sw::Vector2 v2, float t)
		{
			sw::Vector2 temp;
			temp.x = Lerp(v1.x, v2.x, t);
			temp.y = Lerp(v1.y, v2.y, t);

			return temp;
		}*/
	}

	struct Box
	{
		Vector2 BoxScale;
		Vector2 BoxOffset;
		
	};

	typedef Vector2 Vector2D;
	typedef Vector2 Pos;


}