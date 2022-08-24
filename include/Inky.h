#ifndef PACMAN_INKY_H
#define PACMAN_INKY_H

#include "Ghost.h"

//customizable based on Inky's special behaviors
class Inky : public Ghost {
public:
    Inky(sf::Vector2f, GameForm *,bool useTheDoor = true);

    ~Inky() override;

    void update(sf::Time dt) override;
};


#endif //PACMAN_INKY_H
