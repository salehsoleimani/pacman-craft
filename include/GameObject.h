#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameObject {
public:
    enum class ObjectType {
        WALL, PACMAN, FOOD, FOOD_POWER, EMPTY
    };

    GameObject(sf::Vector2f position) : position(position) {}

    virtual void update(sf::Time) = 0;

    virtual void render(sf::RenderTarget *) = 0;

    const sf::Vector2f &getPosition() const {
        return position;
    }

protected:
    ObjectType gameObjectType;

private:
    sf::Vector2f position;
};


#endif //PACMAN_GAMEOBJECT_H