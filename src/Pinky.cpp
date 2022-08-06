#include "Pinky.h"

Pinky::Pinky(sf::Vector2f position, GameForm *context) : Ghost(position, context) {

    animator->add("right", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(0,0), 2);
    animator->add("die", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(0, 0), 8);
    animator->add("frightened", sf::seconds(2), "../res/sprites/frightened.png", sf::Vector2i(0, 0), 8);

}

Pinky::~Pinky() {

}
