#include "Form.h"
#include "GameObject.h"

Form::Form(string mapFileName, Application &context) : mapFileName(mapFileName), context(context) {
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

    //read and insert board map to array
    string line;
    for (int i = 0; i < 26; ++i) {
        line = file.getline();
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            switch (line[j]) {
                case 'W': // WALL
                    board[i][j] = GameObject::ObjectType::WALL;
                    break;
                case 'A': //PACMAN
                    board[i][j] = GameObject::ObjectType::PACMAN;
                    break;
                case 'F': //Normal Food
                    board[i][j] = GameObject::ObjectType::PELLET;
                    break;
                case 'S' ://Power food
                    board[i][j] = GameObject::ObjectType::PELLET_POWER;
                    break;
                case 'E':
                    board[i][j] = GameObject::ObjectType::EMPTY;
                    break;
                case 'I':
                    board[i][j] = GameObject::ObjectType::INKY;
                    break;
                case 'P':
                    board[i][j] = GameObject::ObjectType::PINKY;
                    break;
                case 'B':
                    board[i][j] = GameObject::ObjectType::BLINKY;
                    break;
                case 'C':
                    board[i][j] = GameObject::ObjectType::CLYDE;
                    break;
                case 'H':
                    board[i][j] = GameObject::ObjectType::HEART;
                    break;
            }
        }
    }

    //drawing wall is common for all forms
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < Dimensions::WALL_COL; ++j) {
            if (board[i][j] == GameObject::ObjectType::WALL)
                walls.push_back(new Wall({j * Dimensions::wallSize.x,
                                          i * Dimensions::wallSize.y}));
        }
    }
}

const array<array<GameObject::ObjectType, 19>, 26> &Form::getBoard() const {
    return board;
}

Application &Form::getApplicationContext() {
    return context;
}
