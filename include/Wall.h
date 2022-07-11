#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H

#include "View.h"

using namespace std;

class Wall : public View {
public:

    Wall(sf::Vector2f);

    ~Wall();

    void update(sf::RenderTarget *) override;

private:

    sf::RectangleShape *wall;

};


#endif //PACMAN_WALL_H
