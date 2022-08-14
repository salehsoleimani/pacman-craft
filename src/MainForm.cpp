#include "MainForm.h"

MainForm::MainForm(Application& context) : Form("../res/map_menu.txt",context) {
    initTexts();
    initMenuView();
    initImages();
}

MainForm::~MainForm() {
    delete menuView;
    delete logoIV;
    delete txtCredits;
}

void MainForm::initTexts() {
    txtCredits = new TextView("made with <3 by saleh", {155, 629});
    txtCredits->setCharacterSize(Font::smallFontSize);
    txtCredits->setFillColor(Colors::colorCyan);
}

void MainForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(Config::videoMode.width / 2.f, 355));
    menuView->pushItem("continue");
    menuView->pushItem("options");
    menuView->pushItem("quit");
    menuView->selectItem(0);
}

void MainForm::initImages() {
    logoIV = new sf::RectangleShape({385, 91});
    logoIV->setOrigin(logoIV->getLocalBounds().width / 2, 0);
    logoIV->setPosition(Config::videoMode.width / 2, 208);
    if (!logoSrc.loadFromFile("../res/images/logo.png")) throw runtime_error("Cannot open resource");
    logoIV->setTexture(&logoSrc);
}

void MainForm::pollEvents(sf::Event &event, sf::RenderWindow *window) {
    switch (event.type) {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code) {
                //switching between menu items
                case sf::Keyboard::Enter:
                    switch (menuView->getSelectedItemIndex()) {
                        case 0:
                            getApplicationContext().popForm();
                            break;
                        case 1:
                            getApplicationContext().pushForm(new OptionsForm(getApplicationContext()));
                            break;
                        case 2:
                            window->close();
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

void MainForm::update(sf::RenderWindow *window, const sf::Time &dt) {
}

void MainForm::render(sf::RenderWindow *window) {
    menuView->render(window);
    txtCredits->render(window);
    window->draw(*logoIV);
}