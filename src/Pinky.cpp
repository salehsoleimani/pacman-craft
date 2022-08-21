#include "Pinky.h"

Pinky::Pinky(sf::Vector2f position, GameForm *context) : Ghost(position, context) {

    animator->add("right", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/pinky.png", sf::Vector2i(0, 0), 2);

    targetScatter = {Dimensions::wallSize.x, 4 * Dimensions::wallSize.x};
}

Pinky::~Pinky() = default;

void Pinky::update(sf::Time dt) {

    targetChase = context->getPacmanPosition();
    switch (context->getPacmanDirection()) {
        case Directions::UP:
            targetChase = targetChase - sf::Vector2f{Dimensions::wallSize.x * 4, Dimensions::wallSize.y * 4};
            break;
        case Directions::DOWN:
            targetChase = targetChase + sf::Vector2f{Dimensions::wallSize.x, Dimensions::wallSize.y * 4};
            break;
        case Directions::LEFT:
            targetChase = targetChase - sf::Vector2f{Dimensions::wallSize.x * 4, Dimensions::wallSize.y};
            break;
        case Directions::RIGHT:
            targetChase = targetChase + sf::Vector2f{Dimensions::wallSize.x * 4, Dimensions::wallSize.y};
            break;
        case Directions::INIT:
            break;
    }

    Ghost::update(dt);
}
