#ifndef CAMERAH
#define CAMERAH

#include <cmath>
#include "ray.h"

class camera
{
public:
    camera(
        vec3 lookFrom,
        vec3 lookAt,
        vec3 vUp, 
        float vfov, 
        float aspect)
    {
        vec3 u, v, w;
        float theta = vfov * M_PI / 180;// vfov is top to bottom in degrees
        float halfHeight = tan(theta / 2);
        float halfWidth = aspect * halfHeight;

        origin = lookFrom;
        w = unit_vector(lookFrom - lookAt);
        u = unit_vector(cross(vUp, w));
        v = cross(w, u);

        //lower_left_corner = vec3(-2.0, -1.0, -1.0);
        lower_left_corner = vec3(-halfWidth, -halfHeight, -1.0);
        lower_left_corner = origin - halfWidth * u - halfHeight * v - w;
        //horizontal = vec3(4.0, 0.0, 0.0);
        //horizontal = vec3(2 * halfWidth, 0.0, 0.0);
        horizontal = 2 * halfWidth * u;
        //vertical = vec3(0.0, 2 * halfHeight, 0.0);
        vertical = 2 * halfHeight * v;
        //origin = vec3(0.0, 0.0, 0.0);
    }

    ray getRay(float u, float v)
    {
        return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
    }

    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
};

#endif