#ifndef PACMAN_MENUVIEW_H
#define PACMAN_MENUVIEW_H

#include "TextView.h"
#include <vector>
#include <functional>
#include "Values.h"

using namespace std;

//custom MenuView class for implementing game menus
class MenuView {
public:

    MenuView(sf::Vector2f);

    ~MenuView();

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *);

    void pushItem(const string &);

    int getSelectedItemIndex();

    void selectItem(int i);

private:
    int selectedItem;

    sf::Vector2f position;

    //menu items
    std::vector<TextView *> items;

    //shadow behind textview when selected
    TextView *textShadow;
};


#endif //PACMAN_MENUVIEW_H
