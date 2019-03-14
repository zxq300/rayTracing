#ifndef RAYH
#define RAYH

#include "vec3.h"

class ray
{
public:
    vec3 A;
    vec3 B;
    
    ray() {}
    ray(const vec3 &a, const vec3 &b)
    {
        A = a;
        B = b;
    }
    vec3 origin() const
    {
        return A;
    }
    vec3 direction() const
    {
        return B;
    }
    vec3 point_at_parameter(float t) const
    {
        return A + t * B;
    }
private:
};


vec3 randomInUnitSphere()
{
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
        // betweeen -1 and 1
    }while(p.squaredLength() >= 1.0);// find a point in the unit radius sphere
    return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}


#endif
