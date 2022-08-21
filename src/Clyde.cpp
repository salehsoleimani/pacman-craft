#include "Clyde.h"

Clyde::Clyde(sf::Vector2f position, GameForm *context) : Ghost(position, context) {

    animator->add("right", sf::milliseconds(300), "../res/sprites/clyde.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/clyde.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/clyde.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/clyde.png", sf::Vector2i(0, 0), 2);

    targetScatter = {4 * Dimensions::wallSize.x, 24 * Dimensions::wallSize.x};
}

Clyde::~Clyde() = default;

void Clyde::update(sf::Time dt) {
    //if surrounding pacman radius chase pacman
    if ((relativePosition - context->getPacmanPosition() / Dimensions::wallSize.x).x <= 8 ||
        (relativePosition - context->getPacmanPosition() / Dimensions::wallSize.x).y <= 8)
        targetChase = context->getPacmanPosition();
    else
        targetChase = targetScatter;

    Ghost::update(dt);
}
