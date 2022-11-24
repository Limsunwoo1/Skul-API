#pragma once
#include "Maths.h"
#include <math.h>

#define PI 3.141592

namespace sw
{
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

        // È¸Àü
        inline Vector2 Rotate(const Vector2 value, float degree)
        {
            Vector2 ret = Vector2::Zero;
            float radian = ToRadian(degree);
            ret.x = value.x * cosf(radian) - value.y * sinf(radian);
            ret.y = value.x * sinf(radian) + value.y * cosf(radian);

            return ret;
        }

        inline float Dot(Vector2& v1, Vector2& v2)
        {
            return (v1.x * v2.x) + (v1.y * v2.y);
        }

        inline float Cross(Vector2& v1, Vector2& v2)
        {
            return (v1.x * v2.x) - (v1.y * v2.y);
        }
    }
}