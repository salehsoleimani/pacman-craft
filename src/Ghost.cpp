#include "Ghost.h"
#include <random>

int Ghost::deadGhosts = 0;

Ghost::Ghost(sf::Vector2f position, GameForm *context) : GameObject(position), context(context) {
    ghost.setPosition(position);
    initialPosition = position;

    updateRelativePosition();
    nextTile = relativePosition;

    animator = new Animator(ghost);

    //common animation between all ghosts
    animator->add("die_right", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(120, 0), 8);
    animator->add("die_left", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(60, 0), 8);
    animator->add("die_top", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(180, 0), 8);
    animator->add("die_down", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(0, 0), 8);

    animator->add("frightened", sf::seconds(2), "../res/sprites/frightened.png", sf::Vector2i(0, 0), 8);

    configSpeed();
}

void Ghost::configSpeed() {
    unsigned level = context->getLevel();
    if (level > 128) frightenedDuration = sf::Time::Zero;
    else if (level >= 64) frightenedDuration = sf::seconds(1);
    else if (level >= 32) frightenedDuration = sf::seconds(1);
    else if (level >= 17) frightenedDuration = sf::seconds(2);
    else if (level >= 11) frightenedDuration = sf::seconds(3);
    else if (level >= 6) frightenedDuration = sf::seconds(4);
    else if (level == 5) frightenedDuration = sf::seconds(2);
    else if (level == 4) frightenedDuration = sf::seconds(3);
    else if (level == 3) frightenedDuration = sf::seconds(4);
    else if (level == 2) frightenedDuration = sf::seconds(5);
    else frightenedDuration = sf::seconds(6);

    if (level >= 21) ghostSpeed = .95 * maxSpeed;
    else if (level >= 5) ghostSpeed = .85 * maxSpeed;
    else ghostSpeed = .75 * maxSpeed;

    if (level >= 21) frightenedSpeed = .5 * maxSpeed;
    else if (level >= 5) frightenedSpeed = .55 * maxSpeed;
    else frightenedSpeed = .6 * maxSpeed;

    speed = ghostSpeed;
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
    if (ghostState != GhostState::DEAD)
        ghostState = state;

    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            speed = frightenedSpeed;
            if (animator->getCurrentAnimationId() != "frightened")
                animator->setAnimation("frightened");
            frightenedTimer -= frightenedDuration.asSeconds();
            break;
        case GhostState::CHASE:
            speed = ghostSpeed;
            break;
        case GhostState::SCATTER:
            speed = ghostSpeed;
            break;
        case GhostState::DEAD:
            context->raiseScore((++deadGhosts) * 200);
            //doubling speed when returning home
            speed = 6;
            isDead = true;
            break;
    }
}

void Ghost::update(sf::Time dt) {

    animator->update(dt);

    //move vector
    nextMove = {0, 0};

    //updating move vector
    switch (direction) {
        case Directions::DOWN:
            nextMove.y += speed;
            break;
        case Directions::UP:
            nextMove.y -= speed;
            break;
        case Directions::LEFT:
            nextMove.x -= speed;
            break;
        case Directions::RIGHT:
            nextMove.x += speed;
            break;
        case Directions::INIT:
            nextMove = {0, 0};
            break;
    }

    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            //handling frightened state
            frightenedTimer += dt.asSeconds();
            if (frightenedTimer >= frightenedDuration.asSeconds()) {
                frightenedTimer = 0;
                ghostState = GhostState::CHASE;
                deadGhosts = 0;
                speed = ghostSpeed;
            }
            break;
        case GhostState::CHASE:
            break;
        case GhostState::SCATTER:
            break;
        case GhostState::DEAD:
            break;
    }

    //if ghost places in fixed size grid item
    if (isInTile()) {
        //if ghost was in dead state, and now we reach home
        if (nextTile == initialPosition / Dimensions::wallSize.x) {
            ghostState = GhostState::CHASE;
            isDead = false;
            speed = ghostSpeed;
        }

        //rounding relative position to fixed size grid item
        if (relativePosition != nextTile) {
            ghost.setPosition(nextTile * Dimensions::wallSize.x);
            relativePosition = nextTile;
        }

        //calculating possible routes
        possibleRoutes.clear();
        checkPossibleRoutes();

        Direction nextDirection;

        //if ghost is dead choose the nearest position to ghosts house
        if (isDead) {
            std::sort(possibleRoutes.begin(), possibleRoutes.end(),
                      [&](const Direction &d1, const Direction &d2) -> bool {
                          return sqrt(pow(d1.tile.x - initialPosition.x / Dimensions::wallSize.x, 2) +
                                      pow(d1.tile.y - initialPosition.y / Dimensions::wallSize.x, 2)) <
                                 sqrt(pow(d2.tile.x - initialPosition.x / Dimensions::wallSize.x, 2) +
                                      pow(d2.tile.y - initialPosition.y / Dimensions::wallSize.x, 2));
                      });
            // we want the smallest way which ghost doesn't have to turn back
            int index = 0;
            for (int i = 0; i < possibleRoutes.size(); ++i) {
                if (possibleRoutes[i].tile != lastTile) {
                    index = i;
                    break;
                }
            }
            nextDirection = possibleRoutes[index];
        } else {
            //moving randomly across map
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> randomRoute(0, possibleRoutes.size() - 1);

            nextDirection = possibleRoutes[randomRoute(rng)];
        }
        //don't turn back otherwise you have to
        if (nextDirection.tile != lastTile || possibleRoutes.size() == 1) {
            lastTile = nextTile;
            setDirection(nextDirection.direction);
            nextTile = nextDirection.tile;
        }
    }

    ghost.move(nextMove);

}


bool Ghost::isInTile() {
    updateRelativePosition();
    //approximately placed in tile
    switch (direction) {
        case Directions::INIT:
            return true;
        case Directions::UP:
            if (relativePosition.y <= nextTile.y)
                return true;
            break;
        case Directions::DOWN:
            if (relativePosition.y >= nextTile.y)
                return true;
            break;
        case Directions::LEFT:
            if (relativePosition.x <= nextTile.x)
                return true;
            break;
        case Directions::RIGHT:
            if (relativePosition.x >= nextTile.x)
                return true;
    }
    return false;
}


void Ghost::checkPossibleRoutes() {
    //check if neighbour tiles are free
    auto board = context->getBoard();
    int y = relativePosition.y;
    int x = relativePosition.x;
    if (board[y][x + 1] != GameObject::ObjectType::WALL)
        possibleRoutes.push_back({Directions::RIGHT, {relativePosition.x + 1, relativePosition.y}});
    if (board[y][x - 1] != GameObject::ObjectType::WALL)
        possibleRoutes.push_back({Directions::LEFT, {relativePosition.x - 1, relativePosition.y}});
    if (board[y + 1][x] != GameObject::ObjectType::WALL)
        possibleRoutes.push_back({Directions::DOWN, {relativePosition.x, relativePosition.y + 1}});
    if (board[y - 1][x] != GameObject::ObjectType::WALL)
        possibleRoutes.push_back({Directions::UP, {relativePosition.x, relativePosition.y - 1}});
}

void Ghost::updateRelativePosition() {
    relativePosition = {ghost.getPosition().x / Dimensions::wallSize.x,
                        ghost.getPosition().y / Dimensions::wallSize.x};
}

const Ghost::GhostState &Ghost::getGhostState() const {
    return ghostState;
}

bool Ghost::isColided(const sf::Rect<float> &rect) const {
    return ghost.getGlobalBounds().intersects(rect);
}

void Ghost::setPosition(const sf::Vector2f &pos) {
    ghost.setPosition(pos);
    updateRelativePosition();
    nextTile = relativePosition;
    lastTile = {0, 0};
    frightenedTimer = 0;
}

const sf::Vector2f &Ghost::getInitialPosition() const {
    return initialPosition;
}

void Ghost::setDirection(Directions direction) {
    this->direction = direction;


    //setting animation
    switch (direction) {
        case Directions::DOWN:
            if (ghostState != GhostState::FRIGHTENED && !isDead)
                animator->setAnimation("down");
            else if (isDead)
                animator->setAnimation("die_down");
            break;
        case Directions::UP:
            if (ghostState != GhostState::FRIGHTENED && !isDead)
                animator->setAnimation("up");
            else if (isDead)
                animator->setAnimation("die_up");
            break;
        case Directions::LEFT:
            if (ghostState != GhostState::FRIGHTENED && !isDead)
                animator->setAnimation("left");
            else if (isDead)
                animator->setAnimation("die_left");
            break;
        case Directions::RIGHT:
            if (ghostState != GhostState::FRIGHTENED && !isDead)
                animator->setAnimation("right");
            else if (isDead)
                animator->setAnimation("die_right");
            break;
        case Directions::INIT:
            break;
    }
}
