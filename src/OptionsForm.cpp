#include "OptionsForm.h"

OptionsForm::OptionsForm() : Form("../res/map_menu.txt") {
    initMenuView();
    initImages();
}

OptionsForm::~OptionsForm() {
    delete menuView;
    delete logoIV;
}

void OptionsForm::pollEvents(sf::Event &event, sf::RenderWindow *window, Application *context) {
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                    switch (menuView->getSelectedItemIndex()) {
                        case 0:
                            context->resetGame(new GameForm());
                            break;
                        case 2:
                            context->popForm();
                            break;
                    }
                    break;
                case sf::Keyboard::Down:
                    menuView->selectItem(menuView->getSelectedItemIndex() + 1);
                    break;
                case sf::Keyboard::Up:
                    menuView->selectItem(menuView->getSelectedItemIndex() - 1);
                    break;
            }

    }

}

void OptionsForm::update(sf::RenderWindow *window,const sf::Time& dt) {
}

void OptionsForm::render(sf::RenderWindow *window) {
    menuView->render(window);
    window->draw(*logoIV);
}

void OptionsForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(Config::videoMode.width / 2.f, 355));
    menuView->pushItem("reset");
    menuView->pushItem("clear score");
    menuView->pushItem("back to menu");
}

void OptionsForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(Config::videoMode.width / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}