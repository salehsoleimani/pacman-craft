#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include <array>
#include "Wall.h"
#include "TextView.h"
#include "MainForm.h"
#include "Form.h"
#include "File.h"

using namespace std;

class GameForm : public Form {
public:
    GameForm();
    ~GameForm();
private:
    //views
    TextView *txtScore;
    TextView *txtRecord;

    //methods
    Form* pollEvents(sf::Event&,sf::RenderWindow*) override;

    void update() override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    //displaying grid background
    string mapFileName;

    void initGrid();

    vector<Wall *> walls;

    array<array<char, 19>, 26> board;


};

#endif //PACMAN_GAMEFORM_H
