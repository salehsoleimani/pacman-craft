#ifndef PACMAN_BLINKY_H
#define PACMAN_BLINKY_H

#include "Ghost.h"

class Blinky : public Ghost {
public:
    Blinky(sf::Vector2f, GameForm *);

    ~Blinky();

    void update(sf::Time) override;

};


#endif //PACMAN_BLINKY_H
