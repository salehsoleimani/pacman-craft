#include "GameForm.h"

GameForm::GameForm(){
    this->mapFileName = "../res/map.txt";
    initGrid();
    initTexts();
}

Form *GameForm::pollEvents(sf::Event &event,sf::RenderWindow* window) {
    switch (event.type) {
    }
    return nullptr;
}

void GameForm::update() {
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    for (Wall *wall: walls) wall->render(window);
}

void GameForm::initTexts() {
    txtScore = new TextView("score\n1200", {251, 21});
    txtRecord = new TextView("high score\n3421", {380, 21});
    txtScore->setCharacterSize(Font::smallFontSize);
    txtRecord->setCharacterSize(Font::smallFontSize);
}

void GameForm::initGrid() {
    File file(mapFileName);
    file.open(ios::in);
    string line;
    for (int i = 0; i < 26; ++i) {
        line = file.getline();
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            board[i][j] = line[j];
        }
    }

    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            if (board[i][j] == 'W')
                walls.push_back(new Wall({j * Dimensions::wallSize.x,
                                          i * Dimensions::wallSize.y}));
        }
        cout << endl;
    }
}

GameForm::~GameForm() {
    for(auto wall:walls) delete wall;
}
