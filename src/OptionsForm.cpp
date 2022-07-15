#include "OptionsForm.h"


OptionsForm::OptionsForm() {
//    this->mapFileName = "../res/map_menu.txt";
    initMenuView();
    initImages();
}

OptionsForm::~OptionsForm() {
    delete menuView;
    delete logoIV;
}

Form *OptionsForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                case sf::Keyboard::Enter:
                  if (menuView->getSelectedItemIndex() == 1) {
                        context->pushForm(optionsForm);
//                        context->changeForm(this->context.)
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

    return nullptr;
}

void OptionsForm::update() {
//    pollEvents();
}

void OptionsForm::render(sf::RenderWindow *window) {
//    window->close();
    menuView->render(window);
    window->draw(*logoIV);
}

void OptionsForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(Config::videoMode.width / 2.f, 355));
    menuView->pushItem("reset", [] {});
    menuView->pushItem("clear score", [] { std::cout << "I am working!"; });
    menuView->pushItem("back to menu", [&] {

    });
}

void OptionsForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(Config::videoMode.width / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}