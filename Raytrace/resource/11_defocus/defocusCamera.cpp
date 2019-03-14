#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "sphere.h"
#include "hitablelist.h"
#include "camera.h"
#include "drand48.h"

#define RAYTRACEMAX 10

using namespace std;

// depth is the number of reflections which limits the recursion times
vec3 color(const ray &r, hitable *world, int depth)
{
    hitRecord rec;
    if(world->hit(r, 0.001, MAXFLOAT, rec))// use 0.001 instead of 0 to avoid float bugs
    {
        ray scattered;
        vec3 attenuation;

        if(depth < RAYTRACEMAX && rec.matPtr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * color(scattered, world, depth + 1);
        }
        else
        {
            return vec3(0, 0, 0);
        }
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
    
    hitable *list[5];//
    list[0] = new sphere( vec3(0,0,-1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)) );
    list[1] = new sphere( vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8, 0.8, 0.0)) );
    list[2] = new sphere( vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 1.0) );
    list[3] = new sphere( vec3(-1,0,-1), 0.5, new transparent(1.5) );
    list[4] = new sphere( vec3(-1,0,-1), -0.45, new transparent(1.5) );// can be used to create a bubble

    hitable *world = new hitableList(list, 5);// equal to the length of list[]

    // hitable *list[2];
    // float R = cos(M_PI / 4);
    // list[0] = new sphere( vec3(-R,0,-1), R, new lambertian(vec3(0,0,1)) );
    // list[1] = new sphere( vec3(R,0,-1), R, new lambertian(vec3(1,0,0)) );
    // hitable *world = new hitableList(list, 2);

    // camera cam(90, float(nx)/float(ny));
    //camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 45, float(nx)/float(ny));

    vec3 lookFrom(3, 3, 2);
    vec3 lookAt(0, 0, -1);
    float distToFocus = (lookFrom - lookAt).length();
    float aperture = 2.0;

    camera cam(lookFrom, lookAt, vec3(0,1,0), 20, float(nx) / float(ny), aperture, distToFocus);

    int i = 0, j = 0, s = 0;
    float u = 0, v = 0;
    int ir = 0, ig = 0, ib = 0;
    for(j = ny - 1; j >= 0; j--)
    {
        for(i = 0; i < nx; i++)
        {
            float percent = 0;
            percent = float((i + 1) * (ny - j)) / float(nx * ny);
            cout << percent * 100.0 << "\t %\n";

            vec3 col(0, 0, 0);
            for(s = 0; s < ns; s++)
            {
                u = float(i + drand48()) / float(nx);
                v = float(j + drand48()) / float(ny);
                // drand48() returns random float random number between 0 and 1

                ray r = cam.getRay(u, v);
                
                col = col + color(r, world, 0);// simulate the pixel
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