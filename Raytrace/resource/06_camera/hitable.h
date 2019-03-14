#ifndef HITABLEH
#define HITABLEH

#include "vec3.h"
#include "ray.h"

struct hitRecord
{
    float t;
    vec3 p;
    vec3 normal;// the normal vector from sphere center to hit point
};

class hitable
{
public:
    virtual bool hit(
        const ray &r, 
        float t_min, 
        float t_max, 
        hitRecord &rec
        ) const = 0;
};

#endif