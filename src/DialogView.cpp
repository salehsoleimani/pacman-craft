#include "DialogView.h"

DialogView::DialogView(string dialogTitle, string dialogTxt, string cta, sf::Vector2u size, function<void()> onClick) {
    titleTV = new TextView(dialogTitle, {0, 0});
    txtTV = new TextView(justifyText(dialogTxt), {0, 0});
    ctaBtn = new ButtonView(cta, {0, 0}, ButtonView::ButtonSize::BIG, onClick);
    setFillColor(Colors::colorTransparent);
    setSize({(float) size.x, (float) size.y});
    this->size = size;
    initDialog();
}

string DialogView::justifyText(string str) {
    int width = 21, count = 0;
    ostringstream stream;
    istringstream input;
    input.str(str);
    string word, temp;
    stream << str;

    while (input >> word) {
        count += word.size() + 1;
        if (count <= width) {
            temp += word + ' ';
        } else {
            temp += '\n' + word + ' ';
            count = word.size() + 1;
        }
    }
    return temp;
}

void DialogView::render(sf::RenderTarget *target) {
    target->draw(*this);
    target->draw(dialogBox);
    target->draw(line);
    target->draw(*titleTV);
    target->draw(*txtTV);
    ctaBtn->render(target);
}


void DialogView::initDialog() {
    dialogBox.setSize({394, ctaBtn->getGlobalBounds().height + txtTV->getGlobalBounds().height +
                            titleTV->getGlobalBounds().height + line.getGlobalBounds().height + 214});
    dialogBox.setFillColor(Colors::colorBlue);
    dialogBox.setOrigin({dialogBox.getGlobalBounds().width / 2, dialogBox.getGlobalBounds().height / 2});
    dialogBox.setPosition({(float) size.x / 2, (float) size.y / 2});
    dialogBox.setOutlineColor(Colors::colorCyan);
    dialogBox.setOutlineThickness(-5);

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

    ctaBtn->setButtonPosition(
            {(float) size.x / 2, txtTV->getGlobalBounds().top + txtTV->getGlobalBounds().height + 26});
}

void DialogView::update(sf::RenderTarget *target) {
    ctaBtn->update(sf::Vector2f(sf::Mouse::getPosition()));
}
