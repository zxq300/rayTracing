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
    }while(p.squaredLength() >= 1.0);// firatiohe unit radius sphere
    return p;
}

vec3 reflect(const vec3 &v, const vec3 &n)
{
    return v - 2 * dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float fratio, vec3 &refracted)
{
    vec3 unitVec = unit_vector(v);
    float dt = dot(unitVec, n);
    float discr = 1.0 - fratio * fratio * (1 - dt * dt);
    if(discr > 0)
    {
        refracted = fratio * (unitVec - n * dt) - n * sqrt(discr);
        return true;
    }
    else
    {
        return false;
    }
}

float schlick(float cosine, float ratio)
{
    float r0 = (1 - ratio) / (1 + ratio);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

#endif
