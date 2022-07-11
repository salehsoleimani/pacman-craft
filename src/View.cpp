#include "View.h"

View::View(sf::Vector2f position) {
    this->position = position;
}

void View::render(sf::RenderTarget *target) {
    target->draw(*view);
}

sf::Vector2f View::getPosition() const {
    return position;
}

View::~View() {
    delete view;
}