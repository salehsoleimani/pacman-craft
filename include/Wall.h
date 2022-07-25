#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H

#include "GameObject.h"

class Wall : public GameObject {
public:
    Wall(sf::Vector2f);

    ~Wall();

    void update(sf::Time) override;

    void render(sf::RenderTarget *) override;

private:
    sf::RectangleShape *wall;
};


#endif //PACMAN_WALL_H