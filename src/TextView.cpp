#include "TextView.h"

void TextView::update(sf::RenderTarget *target) {

}

TextView::TextView(string txt,sf::Vector2f position): View(position) {
    font.loadFromFile("../res/fonts/bungee.ttf");
    view = new sf::Text(txt, font);
    txtView = dynamic_cast<sf::Text *>(view);
    txtView->setFillColor(textColor);
    txtView->setPosition(position);
    txtView->setOrigin(txtView->getLocalBounds().width/2.0f,txtView->getLocalBounds().height/2.0f);
}

TextView::~TextView() {
    delete txtView;
}

void TextView::setFontSize(int fontSize) {
    txtView->setCharacterSize(fontSize);
}
