#ifndef PACMAN_WALL_H
#define PACMAN_WALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Wall {
public:

    Wall(sf::Vector2f);

    ~Wall();

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

private:
    sf::Vector2f position;

    sf::RectangleShape *wall;
};


#endif //PACMAN_WALL_H