#include "MainForm.h"


MainForm::MainForm() : Form("../res/map_menu.txt") {
    initTexts();
    initMenuView();
    initImages();
}

MainForm::~MainForm() {
    delete menuView;
    delete logoIV;
    delete txtCredits;
}

void MainForm::pollEvents() {
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

void MainForm::update() {
    pollEvents();
}

void MainForm::render() {
    menuView->render(window);
    txtCredits->render(window);
    window->draw(*logoIV);
}

void MainForm::initTexts() {
    txtCredits = new TextView("made with <3 by saleh", {155, 629});
    txtCredits->setCharacterSize(Font::smallFontSize);
    txtCredits->setFillColor(Colors::colorCyan);
}

void MainForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(window->getSize().x / 2.f, 355));
    menuView->pushItem("play", [] { std::cout << "I am working!"; });
    menuView->pushItem("options", [] { std::cout << "I am working!"; });
    menuView->pushItem("quit", [&] { window->close(); });
}

void MainForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(window->getSize().x / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}