#include "Boid.h"
#include "values.h"
#include <cmath>
#include "utils.h"


Boid::Boid() : position_(0,0), velocity_(10*rand_a_b(-3,3),10*rand_a_b(-3,3)), acceleration_(0,0) {}

Boid::Boid( float x, float y)
{
    position_.x = x ;
    position_.y = y ;
}

pair_t Boid::getPosition() const { return position_ ;}
pair_t Boid::getVelocity() const { return velocity_ ;}
pair_t Boid::getAcceleration() const { return acceleration_ ;}


void Boid::setPositionRandom()
{
    float milX = LVL_W / 2, milY = LVL_H / 2 ;
    position_.x = rand_a_b( milX - CENTER, milX + CENTER );
    position_.y = rand_a_b( milY - CENTER, milY + CENTER);
}

void Boid::setPosition( float x, float y )
{
    position_.x = x ;
    position_.y = y ;
}

void Boid::resetAcceleration()
{
    acceleration_.x = 0 ;
    acceleration_.y = 0 ;
}


void Boid::increasePosition( pair_t pos )
{
    position_ += pos ;
}

void Boid::increaseVelocity( pair_t v )
{
    velocity_ += v;
}

void Boid::increaseAcceleration( pair_t v )
{
    acceleration_ += v;
}

void Boid::flock( flock_t boids )
{
    pair_t ali = align( boids );
    pair_t sep = separation( boids );
    pair_t coh = cohesion( boids );
    increaseAcceleration( ali );
    increaseAcceleration( sep );
    increaseAcceleration( coh );
}

void Boid::update ()
{
    increasePosition( velocity_ );
    increaseVelocity( acceleration_ );
    limit( &velocity_, MAXSPEED );
    resetAcceleration();
}



pair_t Boid::align( flock_t boids )
{
    pair_t steering( 0,0 );
    size_t total = 0;
    flock_t::iterator other = boids.begin() ;
    flock_t::iterator en = boids.end() ;
    for ( ; other!=en; ++other )
    {
        float d = dist( getPosition(), other->getPosition() ) ;
        if ( other->ind != ind &&  d < PERCEPTION_RAD )
        {
            steering += other->getVelocity();
            total++ ;
        }
    }
    if (total > 0)
    {
        div( &steering, (float) total );
        setMagnitude( &steering, MAXSPEED );
        steering -= this->velocity_ ;
        limit( &steering, MAXFORCE );
    }
    return steering ;
}

pair_t Boid::separation( flock_t boids )
{
    pair_t steering( 0,0 );
    size_t total = 0;
    flock_t::iterator other = boids.begin() ;
    flock_t::iterator en = boids.end() ;
    for ( ; other!=en; ++other )
    {
        float d = dist( getPosition(), other->getPosition() ) ;
        if ( other->ind != ind &&  d < PERCEPTION_RAD )
        {
            pair_t diff = getPosition() - other->getPosition() ;
            div( &diff, d );
            steering += diff;
            total++ ;
        }
    }
    if (total > 0)
    {
        div( &steering, (float) total );
        setMagnitude( &steering, MAXSPEED );
        steering -= this->velocity_ ;
        limit( &steering, MAXFORCE );
    }
    return steering ;
}

pair_t Boid::cohesion( flock_t boids )
{
    pair_t steering( 0,0 );
    size_t total = 0;
    flock_t::iterator other = boids.begin() ;
    flock_t::iterator en = boids.end() ;
    for ( ; other!=en; ++other )
    {
        float d = dist( getPosition(), other->getPosition() ) ;
        if ( other->ind != ind &&  d < PERCEPTION_RAD )
        {
            steering += other->getPosition();
            total++ ;
        }
    }
    if (total > 0)
    {
        div( &steering, (float) total );
        steering -= this->position_ ;
        setMagnitude( &steering, MAXSPEED );
        steering -= this->velocity_ ;
        limit( &steering, MAXFORCE );
    }
    return steering ;
}


void Boid::edge()
{
    if ( position_.x > LVL_W ) position_.x = 0;
    if ( position_.x < 0 )     position_.x = LVL_W;
    if ( position_.y > LVL_H ) position_.y = 0;
    if ( position_.y < 0 )     position_.y = LVL_H;
}
