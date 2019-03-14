#ifndef SPHEREH
#define SPHEREH

#include "vec3.h"
#include "ray.h"
#include "hitable.h"

class sphere: public hitable
{
public:
    sphere() {}
    sphere(vec3 cen, float r) : center(cen), radius(r){}
    sphere(vec3 cen, float r, material *m) : center(cen), radius(r), mat(m) {}
    virtual bool hit(const ray &r, float tmin, float tmax, hitRecord &rec) const;
    
    vec3 center;
    float radius;
    material *mat;// abstract type
};

bool sphere::hit(const ray &r, float t_min, float t_max, hitRecord &rec) const
{
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;

    float discr = b * b - 4 * a * c;// check if the ray hits the sphere

    if(discr > 0)
    {
        float temp = 0;
        temp = (-b - sqrt(discr)) / (2.0 * a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.matPtr = mat;// record the material

            return true;
        }
        
        temp = (-b + sqrt(discr)) / (2.0 * a);
        if (temp < t_max && temp > t_min)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / radius;
            rec.matPtr = mat;// record the material

            return true;
        }
    }
    return false;
}

#endif