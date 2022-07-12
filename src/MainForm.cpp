#include "MainForm.h"


MainForm::MainForm() : Form("../res/map_menu.txt") {
    initTexts();
    initMenuView();
}

MainForm::~MainForm() {
    delete menuView;
}

void MainForm::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
        }

    }
}

void MainForm::update() {
    pollEvents();
}

void MainForm::render() {

    menuView->render(window);
    txtCredits->render(window);

}

void MainForm::initTexts() {
    txtCredits = new TextView("made with <3 by saleh", sf::Vector2f(155, 629));
    txtCredits->setCharacterSize(Application::smallFontSize);
    txtCredits->setFillColor(Application::colorCyan);
}

void MainForm::initMenuView() {
    menuView = new MenuView(sf::Vector2f(235, 355));
    menuView->pushItem("play", [] { std::cout << "I am working!"; });
    menuView->pushItem("options", [] { std::cout << "I am working!"; });
    menuView->pushItem("quit", [] { std::cout << "I am working!"; });
}