#ifndef FLOCK_H
#define FLOCK_H


#include "Boid.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include "values.h"

using flock_t = std::vector<Boid> ;
using pair_t = sf::Vector2f ;
using size_t = std::vector<Boid>::size_type ;

class Flock
{
public:
    Flock( int, sf::RenderWindow* ) ;
    void initRandom() ;
    void center() ;

    void draw() ;
    void saveScreenShot() ;

    void Run();
    void closeWindow();
    void seekEvent(sf::Event);
    
    void updatePosition();

private:
    flock_t boids_ ;
    sf::RenderWindow *window_ ;
    int screenShotId_ ;
    bool save_, display_ ;
};


#endif