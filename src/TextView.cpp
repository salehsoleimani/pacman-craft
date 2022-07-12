#include "TextView.h"

void TextView::update(sf::RenderTarget *target) {

}

TextView::TextView(string txt, sf::Vector2f position) {
    this->position = position;
    font.loadFromFile("../res/fonts/bungee.ttf");
    setString(txt);
    setFont(font);
    setFillColor(sf::Color::White);
    setPosition(position);
//    txtView->setOrigin(txtView->getLocalBounds().width/2.0f,0);
}

void TextView::render(sf::RenderTarget *target) {
    target->draw(*this);
}