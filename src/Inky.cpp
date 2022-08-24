#include "Inky.h"
#include "Blinky.h"

Inky::Inky(sf::Vector2f position, GameForm *context,bool useTheDoor) : Ghost(position, context,useTheDoor) {
    ghostType = GhostType::INKY;

    animator->add("right", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(120, 0), 2);
    animator->add("left", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(60, 0), 2);
    animator->add("up", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(180, 0), 2);
    animator->add("down", sf::milliseconds(300), "../res/sprites/inky.png", sf::Vector2i(0, 0), 2);

    targetScatter = {19 * Dimensions::wallSize.x, 24 * Dimensions::wallSize.x};
}

Inky::~Inky() = default;

void Inky::update(sf::Time dt) {

    sf::Vector2f pacmanPosition = context->getPacmanPosition();
    sf::Vector2f twoTilesAhead = pacmanPosition;

    //calculate 2 tiles ahead of pacman based on direction
    switch (context->getPacmanDirection()) {
        case Directions::UP:
            twoTilesAhead = twoTilesAhead - sf::Vector2f{Dimensions::wallSize.x * 2, Dimensions::wallSize.y * 2};
            break;
        case Directions::DOWN:
            twoTilesAhead = twoTilesAhead + sf::Vector2f{Dimensions::wallSize.x, Dimensions::wallSize.y * 2};
            break;
        case Directions::LEFT:
            twoTilesAhead = twoTilesAhead - sf::Vector2f{Dimensions::wallSize.x * 2, Dimensions::wallSize.y};
            break;
        case Directions::RIGHT:
            twoTilesAhead = twoTilesAhead + sf::Vector2f{Dimensions::wallSize.x * 2, Dimensions::wallSize.y};
            break;
        case Directions::INIT:
            break;
    }
    //we draw a vector between two tiles ahead of pacman to blinky's position
    //rotating vector 180 degrees
    for (auto ghost: context->getGhosts()) {
        if (ghost->getGhost() == GhostType::BLINKY)
            targetChase = twoTilesAhead - (ghost->getPosition() - twoTilesAhead);
    }

    Ghost::update(dt);
}
