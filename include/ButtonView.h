#ifndef PACMAN_BUTTONVIEW_H
#define PACMAN_BUTTONVIEW_H

#include "TextView.h"
#include "Values.h"
#include <iostream>

class ButtonView : public TextView {
public:
    //for this game we only need these 2 dimensions
    enum class ButtonSize {
        SMALL,
        BIG
    };

    ButtonView(const string &title, const sf::Vector2f &position, const ButtonView::ButtonSize &buttonSize,
               const function<void()> &onClick);

    ~ButtonView();

    void render(sf::RenderTarget *target);

    //we need this function to set shadow and buttonShape positions
    void setButtonPosition(const sf::Vector2f &position);

    //handling button states
    void eventHandler(const sf::Event &, const sf::Vector2f &);

    //calculate and returns button's width
    float getWidth() const;

private:
    //a function passed to execute on button click
    function<void()> onClick;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape* buttonShape = nullptr;
    sf::RectangleShape* buttonShadow = nullptr;
    void initShapes();
};


#endif