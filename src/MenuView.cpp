#include "MenuView.h"
#include <iostream>

MenuView::MenuView(sf::Vector2f position) {
    this->position = position;
    selectedItem = 0;
    textShadow = new TextView("");
}

void MenuView::pushItem(const string &itemTitle) {
    //set margin based on view rendered before this view
    float yAxis = items.size() == 0 ? position.y : items.back()->getPosition().y +
                                                   //because view origin is 0,0
                                                   items.back()->getLocalBounds().height +
                                                   Dimensions::margin;

    TextView *itemView = new TextView(itemTitle, {position.x, yAxis});
    itemView->setCharacterSize(Font::mediumFontSize);
    itemView->setCenterHorizontal(true);

    items.push_back(itemView);
    //initialization state
//    if (items.size() == 1) {
//        items[0]->setFillColor(Colors::colorActive);
//
//        textShadow = new TextView(items[selectedItem]->getString(),{position.x,items[selectedItem]->getPosition().y + Dimensions::shadowOffset});
//        textShadow->setFillColor(Colors::colorShadow);
//        textShadow->setCharacterSize(Font::mediumFontSize);
//        textShadow->setCenterHorizontal(true);
//    }
}

void MenuView::render(sf::RenderTarget *target) {
    target->draw(*textShadow);

    for (auto item: items) {
        target->draw(*item);
    }
}


MenuView::~MenuView() {
    for (auto item: items) {
        delete item;
    }
}

int MenuView::getSelectedItemIndex() {
    return selectedItem;
}

void MenuView::selectItem(int index) {
    if (index >= items.size() || index < 0) return;
    items[selectedItem]->setFillColor(sf::Color::White);
    selectedItem = index;
    items[selectedItem]->setFillColor(Colors::colorActive);

    textShadow->setFillColor(Colors::colorShadow);
    textShadow->setCharacterSize(Font::mediumFontSize);
    textShadow->setCenterHorizontal(true);
    textShadow->setPosition({position.x, items[index]->getPosition().y + Dimensions::shadowOffset});
    textShadow->setString(items[selectedItem]->getString());
    textShadow->setCenterHorizontal(true);
}
