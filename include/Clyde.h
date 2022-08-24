#ifndef PACMAN_CLYDE_H
#define PACMAN_CLYDE_H

#include "Ghost.h"

//customizable based on clyde's special behaviors
class Clyde : public Ghost {
public:
    Clyde(sf::Vector2f, GameForm *,bool useTheDoor);

    ~Clyde() override;

    void update(sf::Time) override;

};


#endif //PACMAN_CLYDE_H
