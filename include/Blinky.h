#ifndef PACMAN_BLINKY_H
#define PACMAN_BLINKY_H

#include "Ghost.h"

//customizable based on blinky's special behaviors
class Blinky : public Ghost {
public:
    Blinky(sf::Vector2f, GameForm *,bool);

    ~Blinky() override;

    void update(sf::Time) override;
};


#endif //PACMAN_BLINKY_H
