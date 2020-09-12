#include "utils.h"
#include <iostream>
#include <cmath>

int rand_a_b(int a, int b) { return rand() % (b - a) + a; }

float dist( pair_t v1, pair_t v2)
{
    return sqrt( (v2.y-v1.y)*(v2.y-v1.y) + (v2.x-v1.x)*(v2.x-v1.x) );
}

void div( pair_t *vec, float f)
{
    vec->x /= f ;
    vec->y /= f ;
}

void mul( pair_t *v, float f)
{
    v->x *= f;
    v->y *= f ;
}

float magnitude( pair_t *v )
{
    return sqrt(v->x*v->x + v->y*v->y);
}

void limit( pair_t *v, float lim)
{
    float size = magnitude(v);
    if (size > lim)
        div( v, size );
}

void normalize( pair_t *v )
{
    float m = magnitude(v);

    if (m > 0)
        div( v, m );
}

void setMagnitude( pair_t *v, float mag)
{
    normalize(v);
    mul( v, mag );
}