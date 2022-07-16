#ifndef PACMAN_DIALOGVIEW_H
#define PACMAN_DIALOGVIEW_H

#include "ButtonView.h"
#include "TextView.h"

class DialogView : public sf::RectangleShape {
public:
    DialogView(string dialogTitle, string dialogTxt, string cta, sf::Vector2u size);

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *target);

    void initDialog(sf::Vector2u size);

private:
    ButtonView ctaBtn;
    TextView titleTV;
    TextView txtTV;
    sf::RectangleShape dialogBox;
    sf::RectangleShape line;
};

#endif