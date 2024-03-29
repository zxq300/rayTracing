#include <iostream>
#include <fstream>
#include "vec3.h"
#include "ray.h"

using namespace std;

vec3 color(const ray &r)
{
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);// -1<t<1 ==> 0<t<1
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    // lerp between (1,1,1) and (0.5, 0.7, 1)
}

int main()
{
    ofstream ppmFile;
    ppmFile.open("ray.ppm");
    int nx = 200;
    int ny = 100;
    ppmFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    vec3 lowerLeftCorner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);// 4 * 2
    vec3 origin(0.0, 0.0, 0.0);
    
    int i = 0, j = 0;
    float u = 0, v = 0;
    int ir = 0, ig = 0, ib = 0;
    for(j = ny - 1; j >=0; j--)
    {
        for(i = 0; i < nx; i++)
        {
            u = (float)i / nx;
            v = (float)j / ny;
            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
            
            vec3 col = color(r);
            ir = int(255.99 * col[0]);
            ig = int(255.99 * col[1]);
            ib = int(255.99 * col[2]);
            
            ppmFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    ppmFile.close();
}
