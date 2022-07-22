#include "Wall.h"
#include "Values.h"

Wall::Wall(sf::Vector2f position){
    this->position = position;
    wall = new sf::RectangleShape;
    wall->setPosition(position);
    wall->setOrigin(wall->getSize().x / 2, wall->getSize().y / 2);
    wall->setFillColor(Colors::colorWall);
    wall->setOutlineColor(Colors::colorBlue);
    // set a inline border
    wall->setOutlineThickness(-1.f);
    wall->setSize(Dimensions::wallSize);
}

void Wall::update(sf::RenderTarget *target) {

}

Wall::~Wall() {
    delete wall;
}

void Wall::render(sf::RenderTarget *target) {
    target->draw(*wall);
}
