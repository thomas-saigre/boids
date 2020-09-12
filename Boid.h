#ifndef BOID_H
#define BOID_H

#include <SFML/Graphics.hpp>

using pair_t = sf::Vector2f ;

class Boid
{
    using flock_t = std::vector<Boid> ;
    using size_t = std::vector<Boid>::size_type ;
public:
    Boid() ;
    Boid( float, float );

    pair_t getPosition() const ;
    pair_t getVelocity() const ;
    pair_t getAcceleration() const ;
    size_t ind ;

    void setPositionRandom() ;
    void setPosition( float, float );
    void resetAcceleration() ;
    void increasePosition( pair_t );
    void increaseVelocity( pair_t );
    void increaseAcceleration( pair_t );

    void flock( flock_t );
    void update() ;


    pair_t align( flock_t );
    pair_t separation( flock_t );
    pair_t cohesion( flock_t );
    void edge();


/*
    void stayInWindow() ;
*/

private:
    pair_t position_ ;
    pair_t velocity_ ;
    pair_t acceleration_ ;
};



#endif