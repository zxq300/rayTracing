#ifndef CAMERAH
#define CAMERAH

#include <cmath>
#include "ray.h"

vec3 randomInUnitDisk()
{
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(), drand48(), 0) - vec3(1, 1, 0);
    }while(dot(p, p) >= 1.0);
    return p;
}

class camera
{
public:
    camera(
        vec3 lookFrom,
        vec3 lookAt,
        vec3 vUp, 
        float vfov, 
        float aspect,
        float aperture,
        float focusDist)
    {
        float theta = vfov * M_PI / 180;// vfov is top to bottom in degrees
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        lensRadius = aperture / 2;
        origin = lookFrom;
        w = unit_vector(lookFrom - lookAt);
        u = unit_vector(cross(vUp, w));
        v = cross(w, u);

        //lower_left_corner = vec3(-2.0, -1.0, -1.0);
        //lower_left_corner = vec3(-halfWidth, -halfHeight, -1.0);
        lower_left_corner = origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        //horizontal = vec3(4.0, 0.0, 0.0);
        //horizontal = vec3(2 * halfWidth, 0.0, 0.0);
        horizontal = 2 * halfWidth * focusDist * u;
        //vertical = vec3(0.0, 2 * halfHeight, 0.0);
        vertical = 2 * halfHeight * focusDist * v;
        //origin = vec3(0.0, 0.0, 0.0);
    }

    ray getRay(float uu, float vv)
    {
        vec3 rd = lensRadius * randomInUnitDisk();
        vec3 offset = u * rd.x() + v * rd.y();
        return ray(origin + offset, lower_left_corner + uu * horizontal + vv * vertical - origin - offset);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lensRadius;
};

#endif