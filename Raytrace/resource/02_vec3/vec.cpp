#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"

using namespace std;

int main()
{
    ofstream ppmFile;
    ppmFile.open("fade.ppm");
    int nx = 200;
    int ny = 100;
    ppmFile << "P3\n" << nx << " " << ny << "\n255\n";
    
    int i = 0, j = 0;
    float r = 0, g = 0, b = 0;
    int ir = 0, ig = 0, ib = 0;
    for (j = ny - 1; j >= 0; j--)
    {
        for(i = 0; i < nx; i++)
        {
            r = (float)i / nx;
            g = (float)j / ny;
            b = 0.5;
            
            vec3 col(r, g, b);
            ir = int(255.99 * col[0]);
            ig = int(255.99 * col[1]);
            ib = int(255.99 * col[2]);
            
            ppmFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    
    ppmFile.close();
}
