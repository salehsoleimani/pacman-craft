#include "GameForm.h"

GameForm::GameForm(string fileName) {
    File file(fileName);
    file.open(ios::in);
    string line;
    for (int i = 0; i < Application::WALL_ROW; ++i) {
        line = file.getline();
        for (int j = 0; j < Application::WALL_COL; ++j) {
            board[i][j] = line[j];
        }
    }

    for (int i = 0; i < Application::WALL_ROW; ++i) {
        for (int j = 0; j < Application::WALL_COL; ++j) {
            if (board[i][j] == 'W')
                walls.push_back(new Wall(sf::Vector2f(j * Application::wallSize.x,
                                                      i * Application::wallSize.y + 92)));
        }
        cout << endl;
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

    for (Wall *wall: walls) wall->render(window);

    window->display();
}