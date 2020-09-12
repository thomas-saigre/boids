#ifndef UTILS_H
#define UTILS_H

#include <SFML/Graphics.hpp>

using pair_t = sf::Vector2f ;

int rand_a_b( int, int );
float dist( pair_t, pair_t );
void div( pair_t*, float );
void mul( pair_t *, float );
float magnitude( pair_t* );
void limit( pair_t*, float );
void normalize( pair_t* );
void setMagnitude( pair_t*, float );


#endif