#include "BlankTile.h"
#include "Values.h"
#include <iostream>

BlankTile::BlankTile(sf::Vector2f position) : GameObject(position) {
    wall = new sf::RectangleShape;
    wall->setPosition(position);
    //set anchor to center
    wall->setOrigin(wall->getSize().x / 2, wall->getSize().y / 2);
    wall->setFillColor(Colors::colorBlue);
    wall->setOutlineColor(Colors::colorWall);
    // set a inline border
    wall->setOutlineThickness(-1.f);
    wall->setSize(Dimensions::wallSize);

    tileSprite.setPosition(position);

    texture = new sf::Texture;
}

BlankTile::~BlankTile() {
    delete wall;
    delete texture;
}

void BlankTile::render(sf::RenderTarget *target) {
    target->draw(*wall);
    target->draw(tileSprite);
}

void BlankTile::update(sf::Time) {

}

const sf::FloatRect &BlankTile::getGlobalBounds() const {
    return wall->getGlobalBounds();
}

void BlankTile::setObjectType(const ObjectType &objectType) {
    //switching blank tile types

    //delete previous sprite if clicked again and switched the tile mode
    if (this->objectType != ObjectType::INIT && objectType != this->objectType) {
        texture->loadFromFile("../res/empty.png", {0, 0, 30, 30});
        tileSprite.setTexture(*texture);
    }

    this->objectType = objectType;

    wall->setFillColor(sf::Color::Transparent);
    wall->setOutlineColor(sf::Color::Transparent);

    switch (objectType) {
        case ObjectType::WALL:
            wall->setFillColor(Colors::colorWall);
            wall->setOutlineColor(Colors::colorBlue);
            break;
        case ObjectType::PACMAN:
            texture->loadFromFile("../res/sprites/pacman.png", {0, 0, 30, 30});
            break;
        case ObjectType::PELLET:
            texture->loadFromFile("../res/sprites/fruits/pellet.png", {0, 0, 30, 30});
            break;
        case ObjectType::PELLET_POWER:
            texture->loadFromFile("../res/sprites/fruits/power_pellet.png", {0, 0, 30, 30});
            break;
        case ObjectType::INKY:
            texture->loadFromFile("../res/sprites/inky.png", {0, 0, 30, 30});
            break;
        case ObjectType::BLINKY:
            texture->loadFromFile("../res/sprites/blinky.png", {0, 0, 30, 30});
            break;
        case ObjectType::CLYDE:
            texture->loadFromFile("../res/sprites/clyde.png", {0, 0, 30, 30});
            break;
        case ObjectType::PINKY:
            texture->loadFromFile("../res/sprites/pinky.png", {0, 0, 30, 30});
            break;
        case ObjectType::HEART:
            texture->loadFromFile("../res/sprites/heart.png", {0, 0, 30, 30});
            break;
        case ObjectType::BLANK:
            wall->setFillColor(Colors::colorBlue);
            wall->setOutlineColor(Colors::colorWall);
        default:
            break;
    }
    if (texture) {
        texture->setSmooth(true);
        tileSprite.setTexture(*texture);
    }
}
