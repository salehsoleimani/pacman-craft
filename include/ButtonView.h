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

    ButtonView(string title, sf::Vector2f position, ButtonView::ButtonSize buttonSize) : TextView(title,
                                                                                                  {position.x / 2,
                                                                                                   position.y / 2}),
                                                                                         position(position) {
        setFillColor(Colors::colorBlue);
        setCharacterSize(Font::regularFontSize);
        setCenterHorizontal(true);
        size = buttonSize == ButtonSize::SMALL ? Dimensions::BUTTON_SIZE_SMALL : Dimensions::BUTTON_SIZE_BIG;
        initShapes();
    }

    void update(sf::RenderTarget *);

    void render(sf::RenderTarget *target) {
        target->draw(buttonShadow);
        target->draw(buttonShape);
        target->draw(*this);
    }

    void setButtonPosition(sf::Vector2f position) {
        this->position = position;
        buttonShape.setOrigin({buttonShape.getGlobalBounds().width / 2, 0});
        buttonShadow.setOrigin({buttonShadow.getGlobalBounds().width / 2, 0});
        buttonShape.setPosition(position);
        buttonShadow.setPosition({position.x + 8, position.y + 8});
        setPosition({position.x, position.y + size.y/4 });
    }

private:
    sf::Vector2f position;

    sf::Vector2f size;

    sf::RectangleShape buttonShape;
    sf::RectangleShape buttonShadow;

    void initShapes() {
        buttonShape.setSize(size);
        buttonShadow.setSize(size);
        buttonShape.setFillColor(Colors::colorActive);
        buttonShadow.setFillColor(Colors::colorShadow);
        setButtonPosition(position);
    }
};


#endif