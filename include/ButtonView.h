#ifndef PACMAN_BUTTONVIEW_H
#define PACMAN_BUTTONVIEW_H

#include "TextView.h"
#include "Values.h"
#include <iostream>

class ButtonView : public TextView {
public:
    enum class ButtonSize {
        SMALL,
        BIG
    };

    ButtonView(string title, sf::Vector2f position, ButtonView::ButtonSize buttonSize, function<void()> onClick);

    void render(sf::RenderTarget *target);

    void setButtonPosition(sf::Vector2f position);

    void eventHandler(const sf::Event &, const sf::Vector2f &);

private:
    function<void()> onClick;

    sf::Vector2f position;

    sf::Vector2f size;

    sf::RectangleShape buttonShape;
    sf::RectangleShape buttonShadow;

    void initShapes();

};


#endif