#include "MainForm.h"


MainForm::MainForm():Form("../res/map_menu.txt") {
    initTexts();
}

MainForm::~MainForm() {
    delete btnOptions;
    delete btnPlay;
    delete btnQuit;
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

    btnPlay->render(window);
    btnOptions->render(window);
    btnQuit->render(window);
    txtCredits->render(window);

}

void MainForm::initTexts() {
    // make a menu item vector
    btnPlay = new TextView("play", sf::Vector2f(235, 355));
    btnOptions = new TextView("options", sf::Vector2f(198, 428));
    btnQuit = new TextView("quit", sf::Vector2f(236, 501));
    txtCredits = new TextView("made with <3 by saleh", sf::Vector2f(155, 629));
    btnPlay->setFontSize(Application::mediumFontSize);
    btnOptions->setFontSize(Application::mediumFontSize);
    btnQuit->setFontSize(Application::mediumFontSize);
    txtCredits->setFontSize(Application::smallFontSize);
}