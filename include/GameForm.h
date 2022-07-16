#ifndef PACMAN_GAMEFORM_H
#define PACMAN_GAMEFORM_H

#include <array>
#include "Wall.h"
#include "TextView.h"
#include "MainForm.h"
#include "Form.h"
#include "File.h"
#include "ButtonView.h"
#include "DialogView.h"

using namespace std;

class GameForm : public Form {
public:
    GameForm();

    ~GameForm();

private:
    TextView *txtScore;
    TextView *txtRecord;
    TextView *btnBack;

    void pollEvents(sf::Event &, sf::RenderWindow *, Application *) override;

    void update() override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    string mapFileName;

    void initGrid();

    vector<Wall *> walls;

    array<array<char, 19>, 26> board;
};

#endif //PACMAN_GAMEFORM_H
