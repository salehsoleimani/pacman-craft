#include "GameForm.h"

GameForm::GameForm(string fileName):Form(fileName) {
    //intialize wall
    initTexts();
}

void GameForm::pollEvents() {
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
        }

    }
}

void GameForm::update() {
    pollEvents();
}

void GameForm::render() {
    txtRecord->render(window);
    txtScore->render(window);
}

void GameForm::initTexts() {
    txtScore = new TextView("score\n1200", sf::Vector2f(251, 21));
    txtRecord = new TextView("high score\n3421", sf::Vector2f(380, 21));
    txtScore->setCharacterSize(Application::smallFontSize);
    txtRecord->setCharacterSize(Application::smallFontSize);
}
