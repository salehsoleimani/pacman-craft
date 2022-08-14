#include "DialogView.h"

DialogView::DialogView() = default;

void DialogView::initTexts(string dialogTitle, string dialogTxt) {
    titleTV = new TextView(dialogTitle, {0, 0});
    txtTV = new TextView(dialogTxt, {0, 0});
}

void DialogView::render(sf::RenderTarget *target) {
    if (visible) {
        target->draw(*this);
        target->draw(dialogBox);
        target->draw(line);
        target->draw(*titleTV);
        target->draw(*txtTV);
        ctaBtn->render(target);
        //just render text for secondary
        if (secondaryBtn) target->draw(*secondaryBtn);
    }
}

void DialogView::initDialog() {
    //setting transparent background
    setFillColor(Colors::colorTransparent);
    //size is window's size to fullfilling it's width and height
    setSize({(float) size.x, (float) size.y});

    //setting dialog dimensions
    dialogBox.setSize({394, ctaBtn->getGlobalBounds().height + txtTV->getGlobalBounds().height +
                            titleTV->getGlobalBounds().height + line.getGlobalBounds().height + 214});
    dialogBox.setFillColor(Colors::colorBlue);
    dialogBox.setOrigin({dialogBox.getGlobalBounds().width / 2, dialogBox.getGlobalBounds().height / 2});
    dialogBox.setPosition({(float) size.x / 2, (float) size.y / 2});
    dialogBox.setOutlineColor(Colors::colorCyan);
    dialogBox.setOutlineThickness(-5);

    //dialog divider
    line.setSize({394, 5});
    line.setFillColor(Colors::colorCyan);
    line.setPosition({dialogBox.getGlobalBounds().left, dialogBox.getGlobalBounds().top + 84});

    titleTV->setCharacterSize(Font::regularFontSize);
    titleTV->setPosition(
            {getGlobalBounds().width / 2, dialogBox.getGlobalBounds().top + 26});
    titleTV->setCenterHorizontal(true);

    txtTV->setCharacterSize(Font::regularFontSize);
    txtTV->setPosition({getGlobalBounds().width / 2, line.getGlobalBounds().top + line.getGlobalBounds().height + 26});
    txtTV->setCenterHorizontal(true);

    //if we have a secondary btn set it's positions
    if (!secondaryBtn)
        ctaBtn->setButtonPosition(
                {(float) size.x / 2, txtTV->getGlobalBounds().top + txtTV->getGlobalBounds().height + 26});
    else {
        secondaryBtn->setFillColor(sf::Color::White);

        secondaryBtn->setButtonPosition(
                {dialogBox.getGlobalBounds().left + ctaBtn->getWidth() / 2,
                 txtTV->getGlobalBounds().top + txtTV->getGlobalBounds().height + 26});

        ctaBtn->setButtonPosition(
                {dialogBox.getGlobalBounds().left + dialogBox.getGlobalBounds().width - ctaBtn->getWidth() / 2,
                 txtTV->getGlobalBounds().top + txtTV->getGlobalBounds().height + 26});

    }
}

void DialogView::pollEvents(const sf::Event &event, const sf::Window *target) {
    if (ctaBtn) {
        ctaBtn->eventHandler(event, sf::Vector2f(sf::Mouse::getPosition(*target)));
    }
    //check if secondaryBtn is not nullptr - if we have the secondary dialog
    if (secondaryBtn) {
        secondaryBtn->eventHandler(event, sf::Vector2f(sf::Mouse::getPosition(*target)));
    }
}

DialogView::~DialogView() {
    delete ctaBtn;
    delete secondaryBtn;
    delete titleTV;
    delete txtTV;
}

DialogView &DialogView::create(string dialogTitle, string dialogTxt, string cta,
                               const function<void()> &onClick) {
    this->size = {Config::videoMode.width, Config::videoMode.height};

    ctaBtn = new ButtonView(cta, {0, 0}, ButtonView::ButtonSize::BIG, onClick);

    initTexts(dialogTitle, dialogTxt);
    initDialog();

    return *this;
}

DialogView &
DialogView::create(string dialogTitle, string dialogTxt, string cta, string secondaryCta,
                   const function<void()> &onClick, const function<void()> &onSecondaryClick) {
    this->size = {Config::videoMode.width, Config::videoMode.height};

    ctaBtn = new ButtonView(cta, {0, 0}, ButtonView::ButtonSize::SMALL, onClick);
    secondaryBtn = new ButtonView(secondaryCta, {0, 0}, ButtonView::ButtonSize::SMALL, onSecondaryClick);

    initTexts(dialogTitle, dialogTxt);
    initDialog();

    return *this;
}

bool DialogView::show() {
    visible = true;
}

bool DialogView::hide() {
    visible = false;
    delete txtTV;
    delete titleTV;
    delete ctaBtn;
    delete secondaryBtn;
    secondaryBtn = nullptr;
    ctaBtn = nullptr;
    titleTV = nullptr;
    txtTV = nullptr;
}

bool DialogView::isVisible() const {
    return visible;
}