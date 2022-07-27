#include "DialogView.h"

DialogView::DialogView(string dialogTitle, string dialogTxt, string cta, const sf::Vector2u &size,
                       const function<void()> &onClick) : size(size) {

    ctaBtn = new ButtonView(cta, {0, 0}, ButtonView::ButtonSize::BIG, onClick);
    initTexts(dialogTitle, dialogTxt);
    initDialog();
}

DialogView::DialogView(string dialogTitle, string dialogTxt, string cta, string secondaryCta, const sf::Vector2u &size,
                       const function<void()> &onClick) : size(size) {
    ctaBtn = new ButtonView(cta, {0, 0}, ButtonView::ButtonSize::BIG, onClick);
    initTexts(dialogTitle, dialogTxt);
    initDialog();
}

void DialogView::initTexts(string dialogTitle, string dialogTxt) {
    titleTV = new TextView(dialogTitle, {0, 0});
    txtTV = new TextView(justifyText(dialogTxt), {0, 0});
}

//fitting Textview to dialog content area
//line break if passes the line
string DialogView::justifyText(const string &str) {
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
    setFillColor(Colors::colorTransparent);
    setSize({(float) size.x, (float) size.y});

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

void DialogView::pollEvents(const sf::Event &event, const sf::Window *target) {
    ctaBtn->eventHandler(event, sf::Vector2f(sf::Mouse::getPosition(*target)));
}