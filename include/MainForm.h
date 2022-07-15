#ifndef PACMAN_MAINFORM_H
#define PACMAN_MAINFORM_H

#include "Form.h"
#include "Application.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"
#include "GameForm.h"
#include "OptionsForm.h"

class MainForm : public Form {
public:
    MainForm();

    ~MainForm();

private:
    MenuView *menuView;

    TextView *txtCredits;

    sf::Texture logoSrc;
    sf::RectangleShape *logoIV;

    void pollEvents(sf::Event &, sf::RenderWindow *, Application *) override;

    void update() override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initMenuView();

    void initImages();
};


#endif //PACMAN_MAINFORM_H
