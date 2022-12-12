#pragma once
#include "Maths.h"
#include <math.h>

#define PI 3.141592



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

     float lerp(float p1, float p2, float t)
     {
         return (1 - t) * p1 + t * p2;
     }

     sw::Vector2 lerp(sw::Vector2 v1, sw::Vector2 v2, float t)
     {
         sw::Vector2 temp;
         temp.x = lerp(v1.x, v2.x, t);
         temp.y = lerp(v1.y, v2.y, t);

         return temp;
     }
 }
