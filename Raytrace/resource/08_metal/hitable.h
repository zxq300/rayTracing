#ifndef HITABLEH
#define HITABLEH

#include "vec3.h"
#include "ray.h"

class material;// declare first to avoid the hitRecord

struct hitRecord
{
    float t;
    vec3 p;
    vec3 normal;// the normal vector from sphere center to hit point
    material *matPtr;// indicates the material type
};

class material // define after hitRecord
{
public:
    virtual bool scatter(
        const ray &r_in,
        const hitRecord &rec,
        vec3 &attenuation,
        ray &scattered
    ) const = 0;
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

class lambertian:public material// diffuse material
{
public:
    lambertian(const vec3 &a) : albedo(a) {}
    virtual bool scatter(const ray &r_in, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 target = rec.p + rec.normal + randomInUnitSphere();
        // rec.p: hit point
        // rec.normal: the normal vector from hit point
        scattered = ray(rec.p, target - rec.p);
        // calculate the color of the diffuse reflect ray

        attenuation = albedo;
        return true;
    }

    vec3 albedo;
};

class metal:public material// metal material
{
public:
    metal(const vec3 &a) : albedo(a) {}
    metal(const vec3 &a, float f)
    {
        albedo = a;
        if(f < 1)
        {
            fuzz = f;
        }
        else
        {
            fuzz = 1;
        }
    }
    virtual bool scatter(const ray &r_in, const hitRecord &rec, vec3 &attenuation, ray &scattered) const
    {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        if(dot(scattered.direction(), rec.normal) > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    vec3 albedo;
    float fuzz = 0;
};


#endif