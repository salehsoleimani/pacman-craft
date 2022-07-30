#ifndef PACMAN_INKY_H
#define PACMAN_INKY_H

#include "Ghost.h"

class Inky : public Ghost {
public:
    Inky(sf::Vector2f, GameForm *);

    ~Inky();

    void update(sf::Time) override;

};


#endif //PACMAN_INKY_H
