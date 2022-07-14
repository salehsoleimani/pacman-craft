#ifndef PACMAN_OPTIONSFORM_H
#define PACMAN_OPTIONSFORM_H

#include "Form.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"

class OptionsForm : public Form {
public:
    OptionsForm();

    ~OptionsForm();

private:
    MenuView *menuView;

    sf::Texture logoSrc;
    sf::RectangleShape *logoIV;

    Form* pollEvents(sf::Event&,sf::RenderWindow*) override;

    void update() override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initMenuView();

    void initImages();

    //displaying grid background
//    string mapFileName;
//
//    void initGrid();
//
//    vector<Wall *> walls;
//
//    array<array<char, 19>, 26> board;
};


#endif //PACMAN_OPTIONSFORM_H
