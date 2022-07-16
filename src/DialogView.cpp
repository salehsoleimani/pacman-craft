#include "DialogView.h"

DialogView::DialogView(string dialogTitle, string dialogTxt, string cta, sf::Vector2u size) :
        titleTV(dialogTitle,
                {0, 0}),
        txtTV(dialogTxt,
              {0, 0}),
        ctaBtn(cta, {0, 0}, ButtonView::ButtonSize::BIG) {
    setFillColor(Colors::colorTransparent);
    setSize({(float) size.x, (float) size.y});
    initDialog(size);
}

void DialogView::render(sf::RenderTarget *target) {
    target->draw(*this);
    target->draw(dialogBox);
    target->draw(line);
    target->draw(titleTV);
    target->draw(txtTV);
    ctaBtn.render(target);
}

void DialogView::initDialog(sf::Vector2u size) {
    dialogBox.setSize({394, 288});
    dialogBox.setFillColor(Colors::colorBlue);
    dialogBox.setOrigin({dialogBox.getGlobalBounds().width / 2, dialogBox.getGlobalBounds().height / 2});
    dialogBox.setPosition({(float) size.x / 2, (float) size.y / 2});
    dialogBox.setOutlineColor(Colors::colorCyan);
    dialogBox.setOutlineThickness(-5);

    line.setSize({394, 5});
    line.setFillColor(Colors::colorCyan);
    line.setPosition({dialogBox.getGlobalBounds().left, dialogBox.getGlobalBounds().top + 84});

    titleTV.setCharacterSize(Font::regularFontSize);
    titleTV.setPosition(
            {getGlobalBounds().width / 2, dialogBox.getGlobalBounds().top + 26});
    titleTV.setCenterHorizontal(true);
    titleTV.setFillColor(Colors::colorActive);

    txtTV.setCharacterSize(Font::regularFontSize);
    txtTV.setPosition({getGlobalBounds().width / 2, line.getGlobalBounds().top + line.getGlobalBounds().height + 26});
    txtTV.setCenterHorizontal(true);

    ctaBtn.setButtonPosition(
            {(float) size.x / 2, txtTV.getGlobalBounds().top + txtTV.getGlobalBounds().height + 26});
}