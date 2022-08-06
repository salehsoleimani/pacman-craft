#include "Pacman.h"
#include "Ghost.h"
#include <list>

Pacman::Pacman(sf::Vector2f position, GameForm *context) : GameObject(position), context(context) {
    pacman.setPosition(position);

    animator = new Animator(pacman);

    animator->add("right", sf::milliseconds(300), "../res/sprites/pacman.png", sf::Vector2i(30, 0), 5);
    animator->add("left", sf::milliseconds(300), "../res/sprites/pacman.png", sf::Vector2i(30, 60), 5);
    animator->add("up", sf::milliseconds(300), "../res/sprites/pacman.png", sf::Vector2i(30, 30), 5);
    animator->add("down", sf::milliseconds(300), "../res/sprites/pacman.png", sf::Vector2i(30, 90), 5);

    animator->add("die", sf::milliseconds(300), "../res/sprites/pacman_die.png", sf::Vector2i(24, 0), 12, false);

    direction = Directions::INIT;

    updateRelativePosition();
}

Pacman::~Pacman() {

}

void Pacman::pollEvents(sf::Event &event) {
    if (isDead) return;

    if (event.type == sf::Event::KeyPressed)
        switch (event.key.code) {
            case sf::Keyboard::Down:
                direction = Directions::DOWN;
                animator->setAnimation("down");
                break;
            case sf::Keyboard::Up:
                direction = Directions::UP;
                animator->setAnimation("up");
                break;
            case sf::Keyboard::Left:
                direction = Directions::LEFT;
                animator->setAnimation("left");
                break;
            case sf::Keyboard::Right:
                direction = Directions::RIGHT;
                animator->setAnimation("right");
                break;
            default:
                direction = Directions::INIT;
                break;
        }
}

void Pacman::update(sf::Time dt) {

    animator->update(dt);

    //a vector to hold next move coordinates
    int x = speed;

    if (context->getLevel() >= 33) x *= .9;
    else if (context->getLevel() >= 21) x *= 1;
    else if (context->getLevel() >= 5) x *= .9;
    else x *= .8;

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

    nextMove = {((int) nextMove.x), ((int) nextMove.y)};

    sf::Vector2f currentPosition = pacman.getPosition();
    pacman.move(sf::Vector2f(nextMove));

    //eating fruits
    for (auto snack: context->getSnacks()) {
        if (snack->getRelativePosition() == relativePosition && !snack->isEaten()) {
            snack->eat();
            if (snack->getSnackType() == Snack::SnackType::POWER)
                for (auto ghost: context->getGhosts())
                    ghost->changeState(Ghost::GhostState::FRIGHTENED);
            context->raiseScore(snack->getPpt());
        }
    }

    //check collision with ghosts
    for (auto ghost: context->getGhosts()) {
        if (ghost->isColided(pacman.getGlobalBounds()) && !isDead) {
            if (ghost->getGhostState() == Ghost::GhostState::FRIGHTENED) {
                ghost->changeState(Ghost::GhostState::DEAD);
            } else if (ghost->getGhostState() != Ghost::GhostState::DEAD) {
                animator->setAnimation("die");
                isDead = true;
            }
        }
    }

    //destruct class after dying animation
    if (animator->isFinished() && isDead)
        context->lose();

    updateRelativePosition();

    //walking through gates
    if (pacman.getPosition().x >= Dimensions::wallSize.x * Dimensions::WALL_COL)
        pacman.setPosition(-Dimensions::wallSize.x, pacman.getPosition().y);

    else if (pacman.getPosition().x <= -Dimensions::wallSize.x)
        pacman.setPosition(Config::videoMode.width, pacman.getPosition().y);

    else if ((pacman.getPosition().x < 1 / 2 * Dimensions::wallSize.x ||
              (pacman.getPosition().x >
               Dimensions::wallSize.x * (Dimensions::WALL_COL - 1) - 1 / 2 * Dimensions::wallSize.x)) &&
             (direction == Directions::RIGHT || direction == Directions::LEFT))
        return;

    else {
        if (checkCollision(relativePosition.x, relativePosition.y)) {
            pacman.setPosition(currentPosition);

            currentPosition = pacman.getPosition();

            updateRelativePosition();

            if (lastMove != nextMove && !checkCollision(relativePosition.x, relativePosition.y))
                pacman.move(sf::Vector2f(lastMove));

            updateRelativePosition();

            if (checkCollision(relativePosition.x, relativePosition.y))
                pacman.setPosition(currentPosition);

        } else
            lastMove = nextMove;
    }

}

bool Pacman::checkCollision(float x, float y) {
    switch (direction) {
        case Directions::INIT:
            break;
        case Directions::UP:
            if (context->getBoard()[floor(y)][ceil(x)] == ObjectType::WALL ||
                context->getBoard()[floor(y)][floor(x)] == ObjectType::WALL) {
                return true;
            }
            break;
        case Directions::DOWN:
            if (context->getBoard()[ceil(y)][ceil(x)] == ObjectType::WALL ||
                context->getBoard()[ceil(y)][floor(x)] == ObjectType::WALL ||
                //extra condition for not pacman entering ghost's house
                context->getBoard()[ceil(y)][floor(x)] == ObjectType::BLINKY) {
                return true;
            }
            break;
        case Directions::LEFT:
            if (context->getBoard()[floor(y)][floor(x)] == ObjectType::WALL ||
                context->getBoard()[ceil(y)][floor(x)] == ObjectType::WALL) {
                return true;
            }
            break;
        case Directions::RIGHT:
            if (context->getBoard()[floor(y)][ceil(x)] == ObjectType::WALL ||
                context->getBoard()[ceil(y)][ceil(x)] == ObjectType::WALL) {
                return true;
            }
            break;
    }
    return false;
}

void Pacman::updateRelativePosition() {
    relativePosition = {pacman.getPosition().x / Dimensions::wallSize.x,
                        pacman.getPosition().y / Dimensions::wallSize.x};
}

void Pacman::render(sf::RenderTarget *target) {
    target->draw(pacman);
}