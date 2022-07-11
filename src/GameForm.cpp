#include "GameForm.h"

GameForm::GameForm(string fileName) {
    File file(fileName);
    string line;
    for (int i = 0; i < 22; ++i) {
        line = file.getline();
        for (int j = 0; j < line.size(); ++j)
            board[i][j] = line[j];
    }
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
    window->clear(Application::colorBlue);
    window->display();
}