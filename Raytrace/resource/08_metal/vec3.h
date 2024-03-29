//***********************************************************************
//
// vec3 class include an array of 3 elements and some operation functions
// float e[3]
// + - * /
// length unit dot cross distance
//
//***********************************************************************
#pragma once
#ifndef VEC3H
#define VEC3H

#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3
{
public:

    float e[3];

    vec3() {}
    vec3(float e0,float e1, float e2)
    {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline float x() const
    {
        return e[0];
    }
    inline float y() const
    {
        return e[1];
    }
    inline float z() const
    {
        return e[2];
    }

    inline float r() const
    {
        return e[0];
    }
    inline float g() const
    {
        return e[1];
    }
    inline float b() const
    {
        return e[2];
    }

    inline const vec3& operator+() const
    {
        return *this;
    }
    inline vec3 operator-() const
    {
        return vec3(-e[0], -e[1], -e[2]);
    }
    inline float operator[](int i) const
    {
        return e[i];
    }
    inline float& operator[](int i)
    {
        return e[i];
    }

    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator+=(const float t);
    inline vec3& operator-=(const float t);
    
    inline float length() const
    {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }
    inline float squaredLength() const
    {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; 
    }
    inline void make_unit_vector();
    
private:
    
};

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}
inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}
inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}
inline vec3 operator*(const vec3 &v1, const float f2)
{
    return vec3(v1.e[0] * f2, v1.e[1] * f2, v1.e[2] * f2);
}
inline vec3 operator*(const float f1, const vec3 &v2)
{
    return vec3(f1 * v2.e[0], f1 * v2.e[1], f1 * v2.e[2]);
}
inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
    return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}
inline vec3 operator/(const vec3 &v1, const float f2)
{
    return vec3(v1.e[0] / f2, v1.e[1] / f2, v1.e[2] / f2);
}

inline vec3 unit_vector(vec3 v)
{
    return v / v.length();
}
inline float dot(const vec3 &v1, const vec3 &v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}
inline vec3 cross(const vec3 &v1, const vec3 &v2)//cross product
{
    return vec3(
		(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1]),
		(-(v1.e[0] * v2.e[2] - v1.e[2] * v2.e[0])),
		(v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0])
		);
}
inline float distance(const vec3 &v1, const vec3 &v2)
{
    return sqrt((v1.e[0] - v2.e[0]) * (v1.e[0] - v2.e[0])
		+ (v1.e[1] - v2.e[1]) * (v1.e[1] - v2.e[1])
		+ (v1.e[2] - v2.e[2]) * (v1.e[2] - v2.e[2]));
}

#endif
