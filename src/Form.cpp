#include "Form.h"

Form::Form(string mapFileName) : mapFileName(mapFileName) {
    initGrid();
}

void Form::clear(sf::RenderWindow *window) {
    for (Wall *wall: walls) wall->render(window);
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
            if (board[i][j] == 'W')
                walls.push_back(new Wall({j * Dimensions::wallSize.x,
                                          i * Dimensions::wallSize.y}));
        }
    }
}

const array<array<char, 19>, 26> &Form::getBoard() const {
    return board;
}
