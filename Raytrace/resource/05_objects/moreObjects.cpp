#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "sphere.h"
#include "hitablelist.h"

#define MAXFORFLOAT 50.0

using namespace std;

vec3 color(const ray &r, hitable *world)
{
    hitRecord rec;
    if(world->hit(r, 0.0, MAXFORFLOAT, rec))
    {
        return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
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
    ofstream ppmFile;
    ppmFile.open("objects.ppm");
    int nx = 200;
    int ny = 100;
    ppmFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);// 4 * 2
    vec3 origin(0.0, 0.0, 0.0);
    
    hitable *list[2];
    list[1] = new sphere(vec3(0,0,-1), 0.5);
    list[0] = new sphere(vec3(0,-100.5,-1), 100);

    hitable *world = new hitableList(list, 2);

    int i = 0, j = 0;
    float u = 0, v = 0;
    int ir = 0, ig = 0, ib = 0;
    for(j = ny - 1; j >= 0; j--)
    {
        for(i = 0; i < nx; i++)
        {
            u = (float)i / nx;
            v = (float)j / ny;
            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);

            vec3 p = r.point_at_parameter(2.0);
            vec3 col = color(r, world);

            ir = int(255.99 * col[0]);
            ig = int(255.99 * col[1]);
            ib = int(255.99 * col[2]);

            ppmFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    ppmFile.close();
    return 0;
}