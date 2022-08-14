#include "TextView.h"

TextView::TextView(std::string txt, sf::Vector2f position) {
    setString(txt);
    font.loadFromFile("../res/fonts/bungee.ttf");
    setFont(font);
    setPosition(position);
}

void TextView::render(sf::RenderTarget *target) {
    target->draw(*this);
}

//set anchor center
void TextView::setCenterHorizontal(bool isCenter) {
    if (!isCenter) return setOrigin(0, 0);
    setOrigin(getLocalBounds().width / 2.0f, 0);
    setPosition(getPosition());
}

TextView::TextView(string str) : TextView(str,{0,0}){
}