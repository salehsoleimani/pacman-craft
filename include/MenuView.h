#ifndef PACMAN_MENUVIEW_H
#define PACMAN_MENUVIEW_H

#include "Application.h"


class MenuItem {
public:
    MenuItem(TextView* itemView, function<void()> onClick) : itemView(itemView), onClick(onClick) {}

    TextView* itemView;

    function<void()> onClick;
};

class MenuView {
public:

    MenuView(sf::Vector2f);

    ~MenuView();

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

    void pushItem(const string &, const function<void()> &);

    const MenuItem* getSelectedItem();

    int getSelectedItemIndex();

    void selectItem(int i);

private:
    int selectedItem;

    sf::Vector2f position;

    vector<MenuItem *> items;
};


#endif //PACMAN_MENUVIEW_H
