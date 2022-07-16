#include "GameForm.h"

GameForm::GameForm() : Form("../res/map.txt") {
    this->mapFileName = "../res/map.txt";
    initGrid();
    initTexts();
}

void GameForm::pollEvents(sf::Event &event, sf::RenderWindow *window, Application *context) {
    switch (event.type) {
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::IntRect rect(btnBack->getPosition().x, btnBack->getPosition().y,
                                 btnBack->getGlobalBounds().width, btnBack->getGlobalBounds().height);
                if (rect.contains(sf::Mouse::getPosition(*window))) {
                    context->pushForm(new MainForm());
                }
            }
            break;

    }
}

void GameForm::update() {
}

void GameForm::render(sf::RenderWindow *window) {
    txtRecord->render(window);
    txtScore->render(window);
    btnBack->render(window);

    for (Wall *wall: walls) wall->render(window);
}

void GameForm::initTexts() {
    txtScore = new TextView("score\n1200", {251, 21});
    txtRecord = new TextView("high score\n3421", {380, 21});
    btnBack = new TextView("pause\nto menu", {82, 21});
    btnBack->setCharacterSize(Font::smallFontSize);
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
    for (auto wall: walls) delete wall;
}
