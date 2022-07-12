#include "MenuView.h"

MenuView::MenuView(sf::Vector2f position) {
    this->position = position;
}

void MenuView::pushItem(const string &itemTitle, const function<void()> &onClick) {
    sf::Vector2f pos = items.size() == 0 ? position : items.back()->itemView.getPosition();

    TextView itemView(itemTitle, {pos.x, pos.y + Application::margin});
    itemView.setCharacterSize(Application::mediumFontSize);

    items.push_back(new MenuItem(itemView, onClick));
}

void MenuView::render(sf::RenderTarget *target) {
    for (auto const &item: items) {
        target->draw(item->itemView);
    }
}

MenuView::~MenuView() {
    for (auto item: items) {
        delete item;
    }
}
