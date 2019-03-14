#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "drand48.h"

#define MAXFORFLOAT 50.0

using namespace std;

vec3 randomInUnitSphere()
{
    vec3 p;
    do{
        p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1, 1, 1);
        // betweeen -1 and 1
    }while(p.squaredLength() >= 1.0);// find a point in the unit radius sphere
    return p;
}

vec3 color(const ray &r, hitable *world)
{
    hitRecord rec;
    if(world->hit(r, 0.001, MAXFORFLOAT, rec))// use 0.001 instead of 0 to avoid float bugs
    {
        vec3 target = rec.p + rec.normal + randomInUnitSphere();
        // rec.p: hit point
        // rec.normal the normal vector of hit point

        //return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
        return 0.5 * color(ray(rec.p, target - rec.p), world);
        // calculate the color of the diffuse reflect ray by recursion
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main()
{
    int nx = 200;
    int ny = 100;
    int ns = 100;

    ofstream ppmFile;
    ppmFile.open("camera.ppm");
    ppmFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);// 4 * 2
    vec3 origin(0.0, 0.0, 0.0);
    
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1), 0.5);
    list[1] = new sphere(vec3(0,-100.5,-1), 100);

    hitable *world = new hitableList(list, 2);

    camera cam;

    int i = 0, j = 0, s = 0;
    float u = 0, v = 0;
    int ir = 0, ig = 0, ib = 0;
    for(j = ny - 1; j >= 0; j--)
    {
        for(i = 0; i < nx; i++)
        {
            vec3 col(0, 0, 0);
            for(s = 0; s < ns; s++)
            {
                u = float(i + drand48()) / float(nx);
                v = float(j + drand48()) / float(ny);
                // drand48() returns random float random number between 0 and 1

                ray r = cam.getRay(u, v);
                
                col = col + color(r, world);// simulate the pixel
            }

            col = col / float(ns);// sampling pixel from the real world

            col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            // make the color lighter

            ir = int(255.99 * col[0]);
            ig = int(255.99 * col[1]);
            ib = int(255.99 * col[2]);

            ppmFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    ppmFile.close();
    return 0;
}