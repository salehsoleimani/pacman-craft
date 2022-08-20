#ifndef PACMAN_INKY_H
#define PACMAN_INKY_H

#include "Ghost.h"

//customizable based on Inky's special behaviors
class Inky : public Ghost {
public:
    Inky(sf::Vector2f, GameForm *);

    ~Inky();
};


#endif //PACMAN_INKY_H
