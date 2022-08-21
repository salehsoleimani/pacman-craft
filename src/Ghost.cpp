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

    configTimer();
}

void Ghost::configTimer() {
    stateIndex = 0;
    ghostState = GhostState::SCATTER;
    unsigned level = context->getLevel();
    if (level >= 5) stateTimer = {7, 20, 7, 20, 5, 20, 5};
    else if (level >= 2) stateTimer = {7, 20, 7, 20, 5, 1033, 1.0f / 60};
    else stateTimer = {7, 20, 7, 20, 5, 1037, 1.0f / 60};

    frightenedTimer = 0;
    scatterTimer = 0;
    chaseTimer = 0;
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
    if (state != GhostState::FRIGHTENED && state != GhostState::DEAD)
        lastState = ghostState;
    switch (state) {
        case Ghost::GhostState::FRIGHTENED:

            speed = frightenedSpeed;
            if (animator->getCurrentAnimationId() != "frightened") {
                animator->setAnimation("frightened");
                //rotate 180 degrees
                reverseGhost();
            }
            frightenedTimer -= frightenedDuration.asSeconds();
            break;
        case GhostState::CHASE:

            stateIndex++;
            scatterTimer = 0;
            ghostState = GhostState::CHASE;

            speed = ghostSpeed;
            break;
        case GhostState::SCATTER:
            speed = ghostSpeed;

            stateIndex++;
            chaseTimer = 0;
            ghostState = GhostState::SCATTER;

            //rotate 180 degrees on entering scatter mode
            reverseGhost();
            break;
        case GhostState::DEAD:

            //doubled score after eating each ghost
            context->raiseScore((++deadGhosts) * 200);
            //doubling speed when returning home
            speed = 6;
            ghostState = GhostState::DEAD;
            break;
        case GhostState::INIT:
            break;
    }
    ghostState = state;
}

void Ghost::reverseGhost() {
    sf::Vector2f temp = nextTile;
    nextTile = lastTile;
    lastTile = temp;
    setDirection(lastDirection);
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

    //specify target tile and handle ghost state timer
    switch (ghostState) {
        case Ghost::GhostState::FRIGHTENED:
            //handling frightened state
            frightenedTimer += dt.asSeconds();
            if (frightenedTimer >= frightenedDuration.asSeconds()) {
//                ghostState = lastState;

                frightenedTimer = 0;
                deadGhosts = 0;
                speed = ghostSpeed;
            }
            break;
        case GhostState::CHASE:
            chaseTimer += dt.asSeconds();
            if (chaseTimer >= stateTimer[stateIndex] && stateIndex < 6) {
                changeState(GhostState::SCATTER);
            } else
                targetTile = targetChase;
            break;
        case GhostState::SCATTER:
            scatterTimer += dt.asSeconds();
            if (scatterTimer >= stateTimer[stateIndex] && stateIndex <= 6) {
                changeState(GhostState::CHASE);
            } else
                targetTile = targetScatter;
            break;
        case GhostState::DEAD:
            targetTile = initialPosition;
            break;
        case GhostState::INIT:
            targetTile = doorPosition;
            break;
    }

    //if ghost places in fixed size grid item
    if (isInTile()) {
        //if ghost was in dead state, and now we reach home
        if (nextTile == initialPosition / Dimensions::wallSize.x && ghostState == GhostState::DEAD) {
            changeState(lastState);
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

        float grid = Dimensions::wallSize.x;
        float x = targetTile.x, y = targetTile.y;

        //choose the nearest position to target position
        std::sort(possibleRoutes.begin(), possibleRoutes.end(),
                  [&](const Direction &d1, const Direction &d2) -> bool {
                      float side1 = sqrt(pow(d1.tile.x - x / grid, 2) +
                                         pow(d1.tile.y - y / grid, 2));
                      float side2 = sqrt(pow(d2.tile.x - x / grid, 2) +
                                         pow(d2.tile.y - y / grid, 2));
                      //if distance is same perform with directions priority
                      if (side1 == side2)
                          return d1.direction < d2.direction;
                      return side1 < side2;
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
    if (board[y + 1][x] != GameObject::ObjectType::WALL && //never return to ghost house unless ghost you are dead:)
        (board[y + 1][x] != GameObject::ObjectType::BLINKY || ghostState == GhostState::DEAD))
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
    speed = ghostSpeed;
    lastTile = {0, 0};
    configTimer();
}

const sf::Vector2f &Ghost::getInitialPosition() const {
    return initialPosition;
}

void Ghost::setDirection(Directions direction) {
    lastDirection = this->direction;
    this->direction = direction;

    bool isDead = ghostState == GhostState::DEAD;

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

const Ghost::GhostType &Ghost::getGhost() const {
    return ghostType;
}
