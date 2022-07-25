#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameObject {
public:
    GameObject(sf::Vector2f position) : position(position) {}

    virtual void update(sf::Time) = 0;

    virtual void render(sf::RenderTarget *) = 0;

private:
    sf::Vector2f position;
};


#endif //PACMAN_GAMEOBJECT_H