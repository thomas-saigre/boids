#include "Flock.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "utils.h"

#define SF_STYLE sf::Style::Titlebar | sf::Style::Close




Flock::Flock( int n, sf::RenderWindow *win) :  boids_(n), window_(win), screenShotId_(0), save_(false), display_(true)
{
    window_->create(sf::VideoMode(LVL_W, LVL_H), "Boids simulator", SF_STYLE);
}


void Flock::initRandom()
{
    int ind = 0 ;
    flock_t::iterator it = boids_.begin() ;
    flock_t::iterator en = boids_.end() ;
    for ( ; it!=en; ++it )
    {
        it->setPositionRandom() ;
        it->ind = ind;
        ind++;
    }
}

void Flock::center()
{
    flock_t::iterator it = boids_.begin() ;
    flock_t::iterator en = boids_.end() ;
    for ( ; it!=en; ++it )
    {
        it->setPosition(LVL_W/2, LVL_H/2) ;
    }
}

void Flock::draw()
{
    flock_t::iterator boid = boids_.begin() ;
    flock_t::iterator en = boids_.end() ;
    for ( ; boid!=en; ++boid )
    {
        sf::CircleShape bd( TAILLE_BOID );
#ifdef GREEN
        if (boid->ind == 0)
        bd.setFillColor(sf::Color(0,255,0));
        else
#endif
        bd.setFillColor(sf::Color(109, 7, 20));
        bd.setPosition( boid->getPosition() );
        window_->draw( bd );
    }
}


void Flock::saveScreenShot()
{
    std::stringstream name("");
    name << "screenShot" << screenShotId_ << ".png";
    sf::Texture texture ;
    texture.create( LVL_W, LVL_H );
    texture.update( *window_ );
    sf::Image img = texture.copyToImage();
    if (!img.saveToFile(name.str()))
        std::cerr << "Fail to save screenshot\n";
    screenShotId_ ++ ;
}



void Flock::Run()
{
    while (window_->isOpen())
    {
        sf::Event event;
        while (window_->pollEvent(event))
        {
            seekEvent(event);
        }

        window_->clear(sf::Color(150,150,150));
        draw();
        if (display_)
            window_->display();
        if (save_)
            saveScreenShot();

        updatePosition();
        usleep(TPS_ATTENTE);
    }
}



void Flock::seekEvent(sf::Event event)
{
    if ((event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) || (event.type == sf::Event::Closed))
    {
        closeWindow();
    }
    else if ( event.type == sf::Event::KeyPressed )
    {
        switch (event.key.code)
        {
        case sf::Keyboard::F1:
            saveScreenShot();
            break;
        case sf::Keyboard::S:
            save_ = !save_ ;
            break;
        case sf::Keyboard::D:
            display_ = !display_ ;
            break;
        default:
            break;
        }
    }
}

void Flock::closeWindow()
{
    if (window_->isOpen())
        window_->close();
}



void Flock::updatePosition()
{
    flock_t::iterator boid = boids_.begin() ;
    flock_t::iterator en = boids_.end() ;
    for ( ; boid!=en; ++boid )
    {
        boid->edge();
        boid->flock( boids_ );
        boid->update() ; 
    }
}


