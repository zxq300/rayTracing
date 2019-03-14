#pragma once
#ifndef DRAND48H
#define DRAND48H
#include <stdlib.h>
#define rand_m 0x100000000LL
#define rand_c 0xB16
#define rand_a 0x5DEECE66DLL
static unsigned long long seed = 1;

double drand48()
{
	seed = (rand_a * seed + rand_c) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return ((double)x / (double)rand_m);
}

#endif