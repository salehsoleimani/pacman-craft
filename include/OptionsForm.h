#ifndef PACMAN_OPTIONSFORM_H
#define PACMAN_OPTIONSFORM_H

#include "Form.h"
#include "TextView.h"
#include "Wall.h"
#include "MenuView.h"
#include "MainForm.h"

class OptionsForm : public Form {
public:
    OptionsForm();

    ~OptionsForm();

private:
    MenuView *menuView;

    sf::Texture logoSrc;
    sf::RectangleShape *logoIV;

    void pollEvents(sf::Event&,sf::RenderWindow*, Application *) override;

    void update() override;

    void render(sf::RenderWindow *) override;

    void initTexts();

    void initMenuView();

    void initImages();
};


#endif //PACMAN_OPTIONSFORM_H
