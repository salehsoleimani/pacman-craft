#include "TextView.h"

void TextView::update(sf::RenderTarget *target) {

}

TextView::TextView(string txt, sf::Vector2f position) {
    this->position = position;
    font.loadFromFile("../res/fonts/bungee.ttf");
    setString(txt);
    setFont(font);
    setPosition(position);
}

void TextView::render(sf::RenderTarget *target) {
    target->draw(*this);
}

void TextView::setCenterHorizontal(bool isCenter) {
    if (!isCenter) return setOrigin(0, 0);
    setOrigin(getLocalBounds().width / 2.0f, 0);
    setPosition(position);
}
