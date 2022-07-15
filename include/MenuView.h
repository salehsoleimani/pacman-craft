#ifndef PACMAN_MENUVIEW_H
#define PACMAN_MENUVIEW_H

#include "TextView.h"
#include <vector>
#include <functional>
#include "Values.h"

using namespace std;

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

    std::vector<TextView *> items;

    TextView *textShadow;
};


#endif //PACMAN_MENUVIEW_H
