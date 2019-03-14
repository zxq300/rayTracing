#include <iostream>
#include <fstream>
using namespace std;

int main ()
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
            b = 0.2;

            ir = int(255.99 * r);
            ig = int(255.99 * g);
            ib = int(255.99 * b);

            ppmFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    ppmFile.close();
}
