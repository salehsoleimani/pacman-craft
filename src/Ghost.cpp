#include "Ghost.h"

Ghost::Ghost(sf::Vector2f position, GameForm *context) : GameObject(position) {
    ghost.setPosition(position);

    animator = new Animator(ghost);

    //same for all ghosts
    animator->add("die", sf::milliseconds(300), "../res/sprites/ghost_die.png", sf::Vector2i(0, 0), 8, false);

    updateRelativePosition();
}

//Ghost::~Ghost() {
//    delete animator;
//    delete context;
//}

void Ghost::pollEvents(sf::Event &event) {

}

void Ghost::updateRelativePosition() {
    relativePosition = {ghost.getPosition().x / Dimensions::wallSize.x,
                        ghost.getPosition().y / Dimensions::wallSize.x};
}

void Ghost::render(sf::RenderTarget *target) {
    target->draw(ghost);
}
