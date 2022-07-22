#include "ButtonView.h"

ButtonView::ButtonView(string title, sf::Vector2f position, ButtonView::ButtonSize buttonSize, function<void()> onClick)
        : TextView(title, {position.x / 2, position.y / 2}), position(position), onClick(onClick) {
    setFillColor(Colors::colorBlue);
    setCharacterSize(Font::regularFontSize);
    setCenterHorizontal(true);
    size = buttonSize == ButtonSize::SMALL ? Dimensions::BUTTON_SIZE_SMALL : Dimensions::BUTTON_SIZE_BIG;
    initShapes();
}

void ButtonView::render(sf::RenderTarget *target) {
    target->draw(buttonShadow);
    target->draw(buttonShape);
    target->draw(*this);
}

void ButtonView::setButtonPosition(sf::Vector2f position) {
    this->position = position;
    buttonShape.setOrigin({buttonShape.getGlobalBounds().width / 2, 0});
    buttonShadow.setOrigin({buttonShadow.getGlobalBounds().width / 2, 0});
    buttonShape.setPosition(position);
    buttonShadow.setPosition({position.x + 6, position.y + 6});
    setPosition({position.x, position.y + size.y / 4});
}

void ButtonView::initShapes() {
    buttonShape.setSize(size);
    buttonShadow.setSize(size);
    buttonShape.setFillColor(Colors::colorActive);
    buttonShadow.setFillColor(Colors::colorShadow);
    setButtonPosition(position);
}

void ButtonView::eventHandler(const sf::Event &e, const sf::Vector2f &mousePosition) {
    if (buttonShape.getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        switch (e.type) {
            case sf::Event::MouseButtonPressed:
                setPosition({getPosition().x + 6, getPosition().y + 6});
                buttonShape.setPosition({position.x + 6, position.y + 6});
                break;
            case sf::Event::MouseButtonReleased:
                onClick();
                break;
        }
    } else {
        setPosition({position.x, position.y + size.y / 4});
        buttonShape.setPosition({position.x, position.y});
    }
}