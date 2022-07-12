#include "TextView.h"

void TextView::update(sf::RenderTarget *target) {

}

TextView::TextView(string txt, sf::Vector2f position) {
    this->position = position;
    font.loadFromFile("../res/fonts/bungee.ttf");
    txtView = new sf::Text(txt, font);
    txtView->setFillColor(textColor);
    txtView->setPosition(position);
//    txtView->setOrigin(txtView->getLocalBounds().width/2.0f,0);
}

TextView::~TextView() {
    delete txtView;
}

void TextView::setTextColor(const sf::Color &color) {
    txtView->setFillColor(color);
}

void TextView::setFontSize(int fontSize) {
    txtView->setCharacterSize(fontSize);
}

void TextView::render(sf::RenderTarget *target) {
    target->draw(*txtView);
}

sf::Vector2f TextView::getPosition() const {
    return position;
}