#include "Ghost.h"

int Ghost::deadGhosts = 0;

Ghost::Ghost(sf::Vector2f position, GameForm *context) : GameObject(position),context(context) {
    ghost.setPosition(position);

    animator = new Animator(ghost);

    //same for all ghosts
    animator->add("die", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(0, 0), 8);
    animator->add("frightened", sf::seconds(2), "../res/sprites/frightened.png", sf::Vector2i(0, 0), 8);

    animator->update(sf::milliseconds(300));

    updateRelativePosition();
}

Ghost::~Ghost() {
    delete animator;
}

void Ghost::pollEvents(sf::Event &event) {

}

void Ghost::updateRelativePosition() {
    relativePosition = {ghost.getPosition().x / Dimensions::wallSize.x,
                        ghost.getPosition().y / Dimensions::wallSize.x};
}

void Ghost::render(sf::RenderTarget *target) {
    target->draw(ghost);
}

void Ghost::changeState(GhostState state) {
    ghostState = state;
}

void Ghost::update(sf::Time dt) {

    animator->update(dt);

    if (frightenedTimer >= 10) {
        ghostState = GhostState::CHASE;
        frightenedTimer = 0;
        deadGhosts = 0;
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

const Ghost::GhostState &Ghost::getGhostState() const {
    return ghostState;
}

void Ghost::die() {
    ghostState = GhostState::DEAD;
    animator->setAnimation("die");
    context->raiseScore((++deadGhosts) * 200);
}