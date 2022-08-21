#include "Blinky.h"

Blinky::Blinky(sf::Vector2f position, GameForm *context) : Ghost(position, context) {
    ghostType = GhostType::BLINKY;

    animator->add("right", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/blinky.png", sf::Vector2i(0, 0), 2);

    targetScatter = {19 * Dimensions::wallSize.x, 4 * Dimensions::wallSize.x};
}

Blinky::~Blinky() = default;

void Blinky::update(sf::Time dt) {
    targetChase = context->getPacmanPosition();

    Ghost::update(dt);
}