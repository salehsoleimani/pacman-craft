#include "ButtonView.h"

ButtonView::ButtonView(const string &title, const sf::Vector2f &position, const ButtonView::ButtonSize &buttonSize,
                       const function<void()> &onClick)
        : TextView(title, {position.x / 2, position.y / 2}), position(position), onClick(onClick) {
    //set button styles,font size
    setFillColor(Colors::colorBlue);
    setCharacterSize(Font::regularFontSize);
    //TextView method
    setCenterHorizontal(true);
    size = buttonSize == ButtonSize::SMALL ? Dimensions::BUTTON_SIZE_SMALL : Dimensions::BUTTON_SIZE_BIG;
    initShapes();
}

void ButtonView::render(sf::RenderTarget *target) {
    target->draw(*buttonShadow);
    target->draw(*buttonShape);
    target->draw(*this);
}

void ButtonView::setButtonPosition(const sf::Vector2f &position) {
    this->position = position;

    //setting anchor center in view
    buttonShape->setOrigin({buttonShape->getGlobalBounds().width / 2, 0});
    buttonShadow->setOrigin({buttonShadow->getGlobalBounds().width / 2, 0});

    buttonShape->setPosition(position);
    buttonShadow->setPosition({position.x + 6, position.y + 6});

    setPosition({position.x, position.y + size.y / 4});
}

void ButtonView::initShapes() {
    buttonShape = new sf::RectangleShape(size);
    buttonShadow = new sf::RectangleShape(size);

    buttonShape->setFillColor(Colors::colorActive);
    buttonShadow->setFillColor(Colors::colorShadow);

    setButtonPosition(position);
}

void ButtonView::eventHandler(const sf::Event &e, const sf::Vector2f &mousePosition) {
    if (buttonShape->getGlobalBounds().contains(mousePosition.x, mousePosition.y)) {
        switch (e.type) {
            //button long press state - handling long click animation
            case sf::Event::MouseButtonPressed:
                setPosition({getPosition().x + 6, getPosition().y + 6});
                buttonShape->setPosition({position.x + 6, position.y + 6});
                break;
                //button click state
            case sf::Event::MouseButtonReleased:
                onClick();
                break;
            default:
                break;
        }
    } else {
        //if long click state lost (moving mouse to another area)
        setPosition({position.x, position.y + size.y / 4});
        buttonShape->setPosition({position.x, position.y});
    }
}

ButtonView::~ButtonView() {
    delete buttonShape;
    delete buttonShadow;
}

float ButtonView::getWidth() const {
    return getGlobalBounds().width + buttonShape->getGlobalBounds().width + 6;
}
