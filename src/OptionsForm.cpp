#include "OptionsForm.h"


OptionsForm::OptionsForm() : Form("../res/map_menu.txt") {
    initMenuView();
    initImages();
}

OptionsForm::~OptionsForm() {
    delete menuView;
    delete logoIV;
}

void OptionsForm::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Enter:
                        menuView->getSelectedItem()->onClick();
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
}

void OptionsForm::update() {
    pollEvents();
}

void OptionsForm::render() {
    window->close();
    menuView->render(window);
    window->draw(*logoIV);
}

void OptionsForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(window->getSize().x / 2.f, 355));
    menuView->pushItem("reset", [] {});
    menuView->pushItem("clear score", [] { std::cout << "I am working!"; });
    menuView->pushItem("back to menu", [&] {

    });
}

void OptionsForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(window->getSize().x / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}