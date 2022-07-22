#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"
#include <functional>
#include <sstream>

class DialogView : public sf::RectangleShape {
public:
    DialogView(string dialogTitle, string dialogTxt, string cta, sf::Vector2u size ,function<void()> onClick);

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *target);

    void initDialog();

private:
    string justifyText(string text);

    sf::Vector2u size;
    ButtonView* ctaBtn;
    TextView* titleTV;
    TextView* txtTV;
    sf::RectangleShape dialogBox;
    sf::RectangleShape line;
};

#endif