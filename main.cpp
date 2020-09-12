#include "Flock.h"
#include <iostream>
#include <SFML/Graphics.hpp>


int main( int argc, char *argv[] )
{
    int n = (argc==2)?atoi(argv[1]):250 ;

    sf::RenderWindow window;
    Flock fl(n, &window);

    srand( time(NULL) );
    // fl.center();
    fl.initRandom();
    fl.Run() ;

    return 0;

}