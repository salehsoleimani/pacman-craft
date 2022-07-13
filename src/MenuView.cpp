#include "MenuView.h"

MenuView::MenuView(sf::Vector2f position) {
    this->position = position;
    selectedItem = 0;
}

void MenuView::pushItem(const string &itemTitle, const function<void()> &onClick) {
    float yAxis = items.size() == 0 ? position.y : items.back()->itemView->getPosition().y + 2 * Dimensions::margin;
    TextView *itemView = new TextView(itemTitle, {position.x, yAxis});
    itemView->setCharacterSize(Font::mediumFontSize);
    itemView->setCenterHorizontal(true);
    items.push_back(new MenuItem(itemView, onClick));
    if (items.size() == 1)
        items[0]->itemView->setFillColor(Colors::colorActive);
}

void MenuView::render(sf::RenderTarget *target) {
    for (auto item: items) {
        target->draw(*item->itemView);
    }
}


MenuView::~MenuView() {
    for (auto item: items) {
        delete item;
    }
}

const MenuItem *MenuView::getSelectedItem() {
    return items[selectedItem];
}

int MenuView::getSelectedItemIndex() {
    return selectedItem;
}

void MenuView::selectItem(int index) {
    if (index >= items.size() || index < 0) return;
    items[selectedItem]->itemView->setFillColor(sf::Color::White);
    selectedItem = index;
    items[selectedItem]->itemView->setFillColor(Colors::colorActive);
}
