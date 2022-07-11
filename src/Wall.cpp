#include "Wall.h"

Wall::Wall(sf::Vector2f position): View(position) {
    view = new sf::RectangleShape;
    wall = dynamic_cast<sf::RectangleShape *>(view);
    wall->setPosition(position);
    wall->setOrigin(wall->getSize().x/2,wall->getSize().y/2);
    wall->setFillColor(Application::colorWall);
    wall->setOutlineColor(Application::colorBlue);
    wall->setOutlineThickness(2.f);
    wall->setSize(Application::wallSize);
}

void Wall::update(sf::RenderTarget *target) {

}

Wall::~Wall() {
    delete wall;
}
