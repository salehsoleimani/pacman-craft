#include "Ghost.h"
#include <random>

int Ghost::deadGhosts = 0;

Ghost::Ghost(sf::Vector2f position, GameForm *context) : GameObject(position), context(context) {
    ghost.setPosition(position);

    animator = new Animator(ghost);

    //same for all ghosts
    animator->add("die", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(0, 0), 8);
    animator->add("frightened", sf::seconds(2), "../res/sprites/frightened.png", sf::Vector2i(0, 0), 8);

    animator->setAnimation("right");
//    animator->update(sf::milliseconds(300));

    updateRelativePosition();
    direction = Directions::RIGHT;

    nextTile = relativePosition;
}

Ghost::~Ghost() {
    delete animator;
}

void Ghost::pollEvents(sf::Event &event) {

}

void Ghost::render(sf::RenderTarget *target) {
    target->draw(ghost);
}

void Ghost::changeState(GhostState state) {
    ghostState = state;
}

void Ghost::update(sf::Time dt) {

    animator->update(dt);

    int x = speed;

    //normal speeds!
    if (context->getLevel() >= 21) x *= .95;
    else if (context->getLevel() >= 5) x *= .85;
    else x *= .75;

    nextMove = {0, 0};

    switch (direction) {
        case Directions::DOWN:
            nextMove.y += x;
            break;
        case Directions::UP:
            nextMove.y -= x;
            break;
        case Directions::LEFT:
            nextMove.x -= x;
            break;
        case Directions::RIGHT:
            nextMove.x += x;
            break;
        case Directions::INIT:
            nextMove = {0, 0};
            break;
    }

    if (frightenedTimer >= 10) {
        ghostState = GhostState::CHASE;
        frightenedTimer = 0;
        deadGhosts = 0;
    }

    ghost.move(nextMove);

    updateRelativePosition();

    //when we reached a fixed tile switch route
//    cout << "RELATIVE POSITION ISSSSS" << relativePosition.x << "     " << relativePosition.y << "NEXT TYLE    "
//         << nextTile.x << "     " << nextTile.y << endl;
    if (checkCollision(relativePosition.x, relativePosition.y)) {
//    if (relativePosition == nextTile) {
        checkPossibleRoutes();
        cout << "EMPTY" << endl;

        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<std::mt19937::result_type> randomRoute(0,
                                                                             possibleRoutes.size() -
                                                                             1); // distribution in range [1, 6]

        nextTile = possibleRoutes[randomRoute(rng)];


        if (nextTile.x > relativePosition.x) direction = Directions::RIGHT;
        else if (nextTile.x < relativePosition.x) direction = Directions::LEFT;
        else if (nextTile.y > relativePosition.y) direction = Directions::DOWN;
        else if (nextTile.y > relativePosition.y) direction = Directions::UP;

        for (auto v: possibleRoutes) {
            cout << v.x << " and y is " << v.y << endl;
        }

        cout << "SELECTED IS    " << nextTile.x << "    AND Y : " << nextTile.y << endl;
    }


    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            if (animator->getCurrentAnimationId() != "frightened")
                animator->setAnimation("frightened");
            else
                frightenedTimer += dt.asSeconds();
            break;
        case GhostState::CHASE:
            animator->setAnimation("right");
            break;
        case GhostState::SCATTER:
            break;
        case GhostState::DEAD:
            animator->setAnimation("die");
            break;
    }
}


bool Ghost::checkCollision(float x, float y) {
    switch (direction) {
        case Directions::INIT:
            break;
        case Directions::UP:
            if (x == nextTile.x && floor(y) == nextTile.y)
                return true;
            break;
        case Directions::DOWN:
            if (x == nextTile.x && ceil(y) == nextTile.y)
                return true;
            break;
        case Directions::LEFT:
            if (ceil(x) == nextTile.x && y == nextTile.y)
                return true;
            break;
        case Directions::RIGHT:
            if (floor(x) == nextTile.x && y == nextTile.y)
                return true;
    }
    return false;
}


void Ghost::checkPossibleRoutes() {
    if (context->getBoard()[relativePosition.y][relativePosition.x + 1] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({relativePosition.x + 1, relativePosition.y});
    }
    if (context->getBoard()[relativePosition.y][relativePosition.x - 1] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({relativePosition.x - 1, relativePosition.y});
    }
    if (context->getBoard()[relativePosition.y + 1][relativePosition.x] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back({relativePosition.x, relativePosition.y + 1});
    }
    if (context->getBoard()[relativePosition.y - 1][relativePosition.x] !=
        GameObject::ObjectType::WALL) {
        possibleRoutes.push_back(
                {relativePosition.x, relativePosition.y - 1});
    }
}

void Ghost::updateRelativePosition() {
    relativePosition = {ghost.getPosition().x / Dimensions::wallSize.x,
                        ghost.getPosition().y / Dimensions::wallSize.x};
}

const Ghost::GhostState &Ghost::getGhostState() const {
    return ghostState;
}

void Ghost::die() {
    ghostState = GhostState::DEAD;
    animator->setAnimation("die");
    context->raiseScore((++deadGhosts) * 200);
}