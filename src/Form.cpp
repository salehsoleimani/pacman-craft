#include "Form.h"

Form::Form(string mapFileName) : mapFileName(mapFileName) {
    initGrid();
}

void Form::clear(sf::RenderWindow *window) {
    for (auto wall: walls) wall->render(window);
}

Form::~Form() {
    for (auto wall: walls) delete wall;
}

void Form::initGrid() {
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
            switch (board[i][j]) {
                case 'W': //walls
                    walls.push_back(new Wall({j * Dimensions::wallSize.x,
                                              i * Dimensions::wallSize.y}));
                    break;
            }
        }
    }
}

const array<array<char, 19>, 26> &Form::getBoard() const {
    return board;
}
