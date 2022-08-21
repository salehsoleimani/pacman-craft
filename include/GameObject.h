#ifndef PACMAN_GAMEOBJECT_H
#define PACMAN_GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class GameObject {
public:
    enum class ObjectType {
        WALL,
        PACMAN,
        PELLET,
        PELLET_POWER,
        INKY,
        BLINKY,
        CLYDE,
        PINKY,
        HEART,
        EMPTY,
        INIT
    };

    explicit GameObject(sf::Vector2f position) : position(position) {}

    virtual ~GameObject() = default;

    virtual void update(sf::Time) = 0;

    virtual void render(sf::RenderTarget *) = 0;

    const sf::Vector2f &getPosition() const {
        return position;
    }

    const sf::Vector2f &getRelativePosition() const {
        return relativePosition;
    }

    void setRelativePosition(const sf::Vector2f &relativePosition) {
        GameObject::relativePosition = relativePosition;
    }

protected:
    ObjectType gameObjectType = ObjectType::INIT;

    sf::Vector2f position;
    //relative position based on game grids
    sf::Vector2f relativePosition;
};

#endif //PACMAN_GAMEOBJECT_H