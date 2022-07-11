#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include "Application.h"
#include "Wall.h"
#include "TextView.h"
#include "Form.h"
#include "File.h"
#include <array>

using namespace std;

class GameForm : public Form {
public:
    GameForm(string);

private:
    //views
    std::vector<Wall *> walls;
    TextView *txtScore;
    TextView *txtRecord;

    array<array<char, 19>, 22> board;


    //methods
    void pollEvents() override;

    void update() override;

    void render() override;

    void initWalls(string);

    void initTexts();
};

#endif //PACMAN_GAMEFORM_H
