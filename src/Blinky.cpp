#include "Blinky.h"

Blinky::Blinky(sf::Vector2f position, GameForm *context) : Ghost(position, context) {

    animator->add("right", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(0,0), 2);

    animator->setAnimation("right");
    animator->update(sf::milliseconds(300));
}

void Blinky::update(sf::Time dt) {

}

Blinky::~Blinky() {

}